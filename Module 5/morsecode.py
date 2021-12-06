import sys

morse_code = {
    'A':'.-', 'B':'-...',
    'C':'-.-.', 'D':'-..', 'E':'.',
    'F':'..-.', 'G':'--.', 'H':'....',
    'I':'..', 'J':'.---', 'K':'-.-',
    'L':'.-..', 'M':'--', 'N':'-.',
    'O':'---', 'P':'.--.', 'Q':'--.-',
    'R':'.-.', 'S':'...', 'T':'-',
    'U':'..-', 'V':'...-', 'W':'.--',
    'X':'-..-', 'Y':'-.--', 'Z':'--..',
    'a':'.-', 'b':'-...',
    'c':'-.-.', 'd':'-..', 'e':'.',
    'f':'..-.', 'g':'--.', 'h':'....',
    'i':'..', 'j':'.---', 'k':'-.-',
    'l':'.-..', 'm':'--', 'n':'-.',
    'o':'---', 'p':'.--.', 'q':'--.-',
    'r':'.-.', 's':'...', 't':'-',
    'u':'..-', 'v':'...-', 'w':'.--',
    'x':'-..-', 'y':'-.--', 'z':'--..',
    '1':'.----', '2':'..---', '3':'...--',
    '4':'....-', '5':'.....', '6':'-....',
    '7':'--...', '8':'---..', '9':'----.',
    '0':'-----', '_':'..--.-', ', ':'--..--', 
    '.':'.-.-.-','?':'..--..', '/':'-..-.', 
    '-':'-....-', '(':'-.--.', ')':'-.--.-'
}

def encode(msg):
    msg_out = ""
    letter = ""
    # print(morse_code.items(1))
    for i in msg:
        if i == ' ':
            msg_out += '..--.- '
        else:
            for k in morse_code.items():
                # print(k[0])
                # print(msg_out)
                if i == k[0]:
                    msg_out += k[1] + ' '
                # if letter == k[1] and letter == '..--.-':
                #     msg_out += ' '
            # letter = ""
    return msg_out

def Decode(msg):
    msg_out = ""
    letter = ""
    # print(morse_code.items(1))
    for i in msg:
        if i != ' ':
            letter += i
        else:
            for k in morse_code.items():
                # print(k[0])
                if letter == k[1] and letter != '..--.-':
                    msg_out += k[0]
                    break
                if letter == k[1] and letter == '..--.-':
                    msg_out += ' '

            letter = ""
    return msg_out

def main(): 
    message = sys.argv[1]
    message = encode(message)
    print("Encoded Message: " + message)
    result = Decode(message)
    print ("Decoded Message: " + result)

# Executes the main function
if __name__ == '__main__':
    print(f"Arguments count: {len(sys.argv)}")
    for i, arg in enumerate(sys.argv):
        print(f"Argument {i:>6}: {arg}")
    if len(sys.argv) > 2:
        print("malformed input")
    else:
        main()