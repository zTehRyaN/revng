#
# This file is distributed under the MIT License. See LICENSE.md for details.
#

import argparse
import sys

import yaml

from . import remap_metaaddress


def log(message):
    sys.stderr.write(message + "\n")


def main():
    parser = argparse.ArgumentParser(description="Extract and process rev.ng model.")
    parser.add_argument(
        "--remap",
        action="store_true",
        help="Remap MetaAddresses. Implies --json.",
    )
    args = parser.parse_args()

    if args.remap:
        args.json = True

    # Consume YAML generated from revng-efa-extractcfg
    input_file = sys.stdin

    # Decode YAML
    parsed_text = yaml.load(input_file, Loader=yaml.SafeLoader)

    # Remap MetaAddress
    if args.remap:
        parsed_text = remap_metaaddress(parsed_text)

    # Dump as JSON
    print(yaml.dump(parsed_text))
    return 0
