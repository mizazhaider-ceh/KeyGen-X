import sys
import string
import time


#================= fUNCTION ==========================
def validate_pass(password):
    
    print("\n~\033[92m The Genrated Password is : \033[0m",password)
    
    time.sleep(0.5)
    
    print("~~~\033[38;5;220m Wait a second......Checking its strength....\033[0m")
    
    time.sleep(2)
    #======== Function Code =======
    
    check_length = len(password) >= 8 #1st criteria ==== Lenght
    
    check_upper = any(upper.isupper() for upper in password)  #2st criteria ==== Upper Case Character
    
    check_lower = any(lower.islower() for lower in password)  #3st criteria ==== Lower Case Character
    
    check_digit = any(digit.isdigit() for digit in password)  #4st criteria ==== Digit
    
    check_special_character = any(special in string.punctuation for special in password)
    
    result = sum([check_length,check_upper,check_lower,check_digit,check_special_character])
    
    if not check_length:
    
        # Password Strength Logic
    
        print("\n~\033[91m Your Password is Weak \n~(Too Short - Minimum 8 Characters Required) \033[0m")
    
    elif check_length and result > 4:
    
        print("\n~\033[95m Your Password is Strong~(Must use)\033[0m\n~\033[96m Excellent! Your password is secure and best to Use..!\033[0m")
    
    elif check_length and result == 3 or result == 4:
    
        print("\n~\033[96m Password is Medium Strong~(Useable)\033[0m\n~\033[93m Try increasing length at least 12 for strong\033[0m")
    
    else:
    
        print("\n~\033[91mYour Password is weak\033[0m\n~\033[96m Your password is too simple! Try adding uppercase letters, numbers, and special characters to make it stronger.\033[0m")
    
    input("\nPress Any key to Exit......")
    
#============== Main Code =============

print("\n")

print("\033[38;5;220m-----------------------------------------------------------\033[0m")

print("|            \033[96mWelcome to the  ~Strength-Check\033[0m              | ")

print("\033[38;5;220m-----------------------------------------------------------\033[0m")

time.sleep(1)

password = sys.argv[1]  

validate_pass(password)

