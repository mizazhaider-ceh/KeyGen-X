import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

from keycheck import assess_password


def test_strong_password():
    verdict, checks = assess_password("Ab3!xYz9Qw")
    assert verdict == "strong"
    assert all(checks.values())


def test_weak_short_password():
    verdict, _ = assess_password("Ab1!")
    assert verdict == "weak"


def test_medium_password():
    verdict, checks = assess_password("Abcdef12")
    assert verdict == "medium"
    assert checks["length (min 8 chars)"]


def test_weak_simple_password():
    verdict, _ = assess_password("abcdefgh")
    assert verdict == "weak"


def test_empty_password_is_weak():
    verdict, _ = assess_password("")
    assert verdict == "weak"


def test_missing_digit_and_special_is_medium():
    verdict, _ = assess_password("Abcdefgh")
    assert verdict == "medium"
