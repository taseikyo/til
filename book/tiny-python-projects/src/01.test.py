#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2020-08-03 17:47:41
# @Author  : Lewis Tian (taseikyo@gmail.com)
# @Link    : github.com/taseikyo
# @Version : Python 3.8.5

import os
from subprocess import getstatusoutput, getoutput

prg = "01.hello.py"


def test_exists():
    """exists"""

    assert os.path.isfile(prg)


def test_runnable():
    """Runs using python3"""

    out = getoutput(f"python3 {prg}")
    assert out.lower().startswith("usage")


def test_executable():
    """Says 'Hello, World!' by default"""

    out = getoutput(prg)
    assert out.lower().startswith("usage")


def test_usage():
    """usage"""

    for flag in ["-h", "--help"]:
        rv, out = getstatusoutput(f"{prg} {flag}")
        assert rv == 0
        assert out.lower().startswith("usage")


def test_input():
    """test for input"""

    for val in ["Universe", "Multiverse"]:
        for option in ["-n", "--name"]:
            rv, out = getstatusoutput(f"{prg} {option} {val}")
            assert rv == 0
            assert out.strip() == f"Hello, {val}!"
