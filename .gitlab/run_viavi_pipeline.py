#!/usr/bin/env python3

import argparse
from dataclasses import dataclass
import pathlib
from typing import List

try:
    import yaml
except ImportError:
    print("Install pyyaml: https://pypi.org/project/PyYAML/")
    exit(1)

try:
    import gitlab
except ImportError:
    print("Install Gitlab Python library: https://pypi.org/project/python-gitlab/")
    exit(1)

DEFAULT_BUILD_ARGS = '-DCMAKE_BUILD_TYPE=Release -DFORCE_DEBUG_INFO=True -DENABLE_UHD=False -DENABLE_DPDK=True -DENABLE_ZEROMQ=False -DMARCH="x86-64-v4"'
DEFAULT_DPDK_VERSION = "23.11.1_avx512"

# pylint: disable=too-many-instance-attributes
@dataclass
class _TestDefinition:
    """
    """

    campaign_filename: str = ""
    id: str = ""
    description: str = ""

# pylint: disable=too-many-instance-attributes
@dataclass
class _ArgsDefinition:
    """
    """

    testlist: bool = False
    token: str = ""
    branch: str = ""
    testid: str = ""
    campaign_path: str = ""
    timeout: int = ""
    gnb_extra: str = ""
    build_args: str = DEFAULT_BUILD_ARGS
    dpdk_version: str = DEFAULT_DPDK_VERSION

def get_viavi_tests():
    viavi_test_declaration = (pathlib.Path(__file__).parent / '..' / 'tests' / 'e2e' / 'tests' / 'viavi' / 'test_declaration.yml').resolve()
    with open(viavi_test_declaration, 'r') as file:
        data = yaml.safe_load(file)

    test_list : List[_TestDefinition] = []
    for test in data['tests']:
        test_definition = _TestDefinition()
        test_definition.campaign_filename = test['campaign_filename']
        test_definition.id = test['id']
        test_definition.description = test.get('description', '')
        test_list.append(test_definition)
    return test_list

def validate_args(args) -> _ArgsDefinition:
    args_definition = _ArgsDefinition()
    args_definition.testlist = args.testlist
    args_definition.token = args.token
    args_definition.branch = args.branch
    args_definition.testid = args.testid
    args_definition.timeout = args.timeout
    args_definition.gnb_extra = args.srsgnb_extra
    args_definition.build_args = args.build_args
    args_definition.dpdk_version = args.dpdk_version

    if not args_definition.testlist:
        fail_validate = False
        if not args_definition.token:
            print("Token is required to run a test.")
            fail_validate = True
        if not args_definition.branch:
            print("Branch is required to run a test.")
            fail_validate = True
        if not args_definition.testid:
            print("Testid is required to run a test.")
            fail_validate = True

        if fail_validate:
            exit(1)
    return args_definition

def show_test_list():
    test_list = get_viavi_tests()
    print("Available tests:")
    for test in test_list:
        print(f"    ⊛ id: {test.id}")
        print(f"        · Description: {test.description}")
        print()


def run_test(args_definition: _ArgsDefinition, test_definition: _TestDefinition):
    timeout = args_definition.timeout if args_definition.timeout else 972800
    retina_log_level = "warning"
    branch = args_definition.branch
    private_token = args_definition.token

    INFRASTRUCTURE_TAG = "amd64-avx2-avx512"
    OS_NAME = "ubuntu-24.04"
    COMPILER = "gcc"
    TESTMODE = "none"

    MAKE_ARGS = "-j6"
    BUILD_ARGS = args_definition.build_args
    DPDK_VERSION = args_definition.dpdk_version

    TESTBED = "viavi"
    MARKERS = "viavi_manual"

    PYARGS = f'--viavi-manual-campaign-filename "{test_definition.campaign_filename}" --viavi-manual-test-name "{test_definition.id}" --viavi-manual-test-timeout {timeout} --retina-pod-timeout 900'
    if args_definition.gnb_extra:
        PYARGS += f' --viavi-manual-extra-gnb-arguments "{args_definition.gnb_extra}"'

    RETINA_ARGS = "gnb.all.pcap=True gnb.all.rlc_enable=True gnb.all.rlc_rb_type=srb"

    variables = [
        {"key": "INFRASTRUCTURE_TAG", "value": INFRASTRUCTURE_TAG},
        {"key": "OS", "value": OS_NAME},
        {"key": "COMPILER", "value": COMPILER},
        {"key": "TEST_MODE", "value": TESTMODE},
        {"key": "BUILD_ARGS", "value": BUILD_ARGS},
        {"key": "MAKE_ARGS", "value": MAKE_ARGS},
        {"key": "UHD_VERSION", "value": ""},
        {"key": "DPDK_VERSION", "value": DPDK_VERSION},
        {"key": "TESTBED", "value": TESTBED},
        {"key": "MARKERS", "value": MARKERS},
        {"key": "KEYWORDS", "value": ""},
        {"key": "PYTEST_ARGS", "value": PYARGS},
        {"key": "RETINA_ARGS", "value": RETINA_ARGS},
        {"key": "E2E_LOG_LEVEL", "value": retina_log_level},
        {"key": "GROUP", "value": "viavi"},
        {"key": "PIPELINE_DESCRIPTION", "value": "Viavi manual test"},
    ]

    print(f"Creating Viavi pipeline for branch {branch}...")
    print(f"    - Test ID: {test_definition.id}")
    print(f"    - Extra arguments to gnb binary: {args_definition.gnb_extra}")
    print(f"    - BUILD_ARGS {BUILD_ARGS}")
    print(f"    - DPDK_VERSION {DPDK_VERSION}")
    print(f"    - OS {OS_NAME}")

    gl = gitlab.Gitlab("https://gitlab.com", private_token=private_token)
    project = gl.projects.get("softwareradiosystems/srsgnb")
    pipeline = project.pipelines.create({"ref": branch, "variables": variables})

    pipeline_url = pipeline.web_url

    print(f"Pipeline created: {pipeline_url}")
def main():
    """
    Entrypoint runner.
    """
    parser = argparse.ArgumentParser(description="List the available tests (--testlist) or run a test.")
    parser.add_argument(
        "--testlist",
        action="store_true",
        help="List of tests to run.",
    )

    parser.add_argument(
        "--token",
        help="[REQUIRED] Gitlab private token: https://docs.gitlab.com/ee/user/profile/personal_access_tokens.html#create-a-personal-access-token",
    )

    parser.add_argument("--branch", help="[REQUIRED] Remote branch in srsgnb repository.")

    parser.add_argument(
        "--testid",
        help='[REQUIRED] Testid in the campaign.',
    )

    parser.add_argument(
        "--srsgnb-extra",
        default="",
        help='Extra agruments passed to the gnb binary. E.g: "log --metrics_level=info"',
    )

    parser.add_argument(
        "--build-args",
        help=f'Build arguments for the pipeline. Default: "{DEFAULT_BUILD_ARGS}"',
        default=DEFAULT_BUILD_ARGS,
    )

    parser.add_argument(
        "--dpdk-version",
        help=f'DPDK version to use in the pipeline. Default: "{DEFAULT_DPDK_VERSION}"',
        default=DEFAULT_DPDK_VERSION,
    )

    parser.add_argument(
        "--timeout", help="Timeout in seconds for the test"
    )

    args_definition = validate_args(parser.parse_args())
    if args_definition.testlist:
        show_test_list()
    else:
        test_list = get_viavi_tests()
        for test_definition in test_list:
            if test_definition.id == args_definition.testid:
                run_test(args_definition, test_definition)
                break
        else:
            print(f"Testid {args_definition.testid} not found.")
        exit(1)

if __name__ == "__main__":
    main()
