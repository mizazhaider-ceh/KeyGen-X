import sys
import string
import time


#================= FUNCTIONS ==========================

def assess_password(password):
    """Evaluate password strength against five criteria.

    Returns a tuple (verdict, checks) where verdict is one of
    "weak", "medium" or "strong", and checks is a dict of the
    individual criteria results. Pure function, easy to test.
    """
    checks = {
        "length (min 8 chars)": len(password) >= 8,
        "uppercase letter": any(c.isupper() for c in password),
        "lowercase letter": any(c.islower() for c in password),
        "digit": any(c.isdigit() for c in password),
        "special character": any(c in string.punctuation for c in password),
    }

    score = sum(checks.values())

    if not checks["length (min 8 chars)"]:
        verdict = "weak"
    elif score == 5:
        verdict = "strong"
    elif score >= 3:
        verdict = "medium"
    else:
        verdict = "weak"

    return verdict, checks


def print_report(password):
    """Pretty-print the strength analysis for a password."""
    print("\n~\033[92m The Generated Password is : \033[0m", password)

    time.sleep(0.5)

    print("~~~\033[38;5;220m Wait a second......Checking its strength....\033[0m")

    time.sleep(1)

    verdict, checks = assess_password(password)

    if verdict == "weak" and not checks["length (min 8 chars)"]:
        print("\n~\033[91m Your Password is Weak \n~(Too Short - Minimum 8 Characters Required) \033[0m")
    elif verdict == "strong":
        print("\n~\033[95m Your Password is Strong~(Must use)\033[0m\n~\033[96m Excellent! Your password is secure and best to Use..!\033[0m")
    elif verdict == "medium":
        print("\n~\033[96m Password is Medium Strong~(Useable)\033[0m\n~\033[93m Try increasing length at least 12 for strong\033[0m")
    else:
        print("\n~\033[91mYour Password is weak\033[0m\n~\033[96m Your password is too simple! Try adding uppercase letters, numbers, and special characters to make it stronger.\033[0m")


def read_password():
    """Get the password to check.

    Priority: piped stdin (how KeyGen-X.cpp sends it) first,
    then the first command line argument, for standalone use.
    """
    if not sys.stdin.isatty():
        piped = sys.stdin.read().strip()
        if piped:
            return piped
    if len(sys.argv) > 1:
        return sys.argv[1]
    print("Error: no password provided. Pipe one via stdin or pass it as an argument.", file=sys.stderr)
    sys.exit(1)


#============== Main Code =============

def main():
    print("\n")

    print("\033[38;5;220m-----------------------------------------------------------\033[0m")

    print("|            \033[96mWelcome to the  ~Strength-Check\033[0m              | ")

    print("\033[38;5;220m-----------------------------------------------------------\033[0m")

    time.sleep(0.5)

    password = read_password()

    print_report(password)

    try:
        input("\nPress Any key to Exit......")
    except EOFError:
        # stdin is not a terminal (e.g. called from KeyGen-X.cpp), just exit
        pass


if __name__ == "__main__":
    main()
