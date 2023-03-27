exponent_constant = 127

def decimal_to_binary_direct_order(decimal):
    bits = []
    ticks_of_bits = 0
    if abs(decimal) < 100:
        number_of_bits = 8
    else:
        number_of_bits = 16
    if decimal < 0:
        decimal = -decimal
        sign_bit = 1
    else:
        sign_bit = 0
    if decimal == 0:
        bits.append(0)
    while decimal >= 1:
        bit = int(decimal % 2)
        bits.append(bit)
        ticks_of_bits += 1
        decimal //= 2
    if ticks_of_bits < number_of_bits:
        bits.extend([0] * (number_of_bits - ticks_of_bits))
    bits.append(sign_bit)
    return bits[::-1]



def decimal_to_binary_reverse_order(decimal):
    binary_number = decimal_to_binary_direct_order(decimal)
    if decimal > 0:
        return binary_number
    else:
        inverted = [1]
    for i in range(1, len(binary_number)):
        if binary_number[i] == 1:
            inverted.append(0)
        else:
            inverted.append(1)
    return inverted

def add_binary_strings(list1, list2):
    result = []
    carry = 0
    max_len = max(len(list1), len(list2))

    list1 = [0] * (max_len - len(list1)) + list1
    list2 = [0] * (max_len - len(list2)) + list2

    for i in range(max_len - 1, -1, -1):
        bit_sum = int(list1[i]) + int(list2[i]) + carry
        result.insert(0, bit_sum % 2)
        carry = bit_sum // 2

    if carry != 0:
        result.insert(0, carry)
    return result


def decimal_to_binary_additional_order(decimal):
    additional_binary = []
    inverted = decimal_to_binary_reverse_order(decimal)
    if decimal < 0:
        temp_list = ['1']
        additional_binary = add_binary_strings(inverted,temp_list )
        return additional_binary
    else:
        return decimal_to_binary_direct_order(decimal)




def length_comparison(list1, list2):
    max_length = max(len(list1), len(list2))
    if list1[0] and list2[0] == 0:
        list1 = [0] * (max_length - len(list1)) + list1
        list2 = [0] * (max_length - len(list2)) + list2
    if list1[0] == 1:
        list1 = [1] * (max_length - len(list1)) + list1
    if list2[0] == 1:
        list2 = [1] * (max_length - len(list2)) + list2
    print(list1,list2)
    return list1, list2


def sum_of_binary_numbers(list1, list2):
    list1, list2 = length_comparison(list1, list2)
    remainder = 0
    temp = 0
    sum_of_numbers = []
    for i in reversed(range(0, len(list1))):
        remainder = (int(list1[i]) + int(list2[i]))
        if remainder == 0 and temp == 0:
            sum_of_numbers.insert(0, 0)
            temp = 0
        elif remainder == 0 and temp == 1:
            sum_of_numbers.insert(0, 1)
            temp = 0
        elif remainder == 1 and temp == 0:
            sum_of_numbers.insert(0, 1)
            temp = 0
        elif remainder == 1 and temp == 1:
            sum_of_numbers.insert(0, 0)
            temp = 1
        elif remainder == 2 and temp == 0:
            sum_of_numbers.insert(0, 0)
            temp = 1
        elif remainder == 2 and temp == 1:
            sum_of_numbers.insert(0, 1)
            temp = 1
    if temp > 0:
        sum_of_numbers.insert(0, 1)
    print(sum_of_numbers)
    return sum_of_numbers

def from_additional_to_reverse(binary_number):
    index_of_first_1 = 0
    for i in reversed(range(len(binary_number))):
        if binary_number[i] == 1:
            index_of_first_1 = i
            binary_number[i] = 0
            break
    for i in range(index_of_first_1 + 1, len(binary_number)):
        binary_number[i] = 1
    return binary_number

def from_reverse_to_direct(binary_number):
    for i in range(1, len(binary_number)):
        if binary_number[i] == 1:
            binary_number[i] = 0
        else:
            binary_number[i] = 1
    return binary_number

def binary_multiplication(list1, list2):
    list1 = list1[1:]
    list2 = list2[1:]
    
    result_length = len(list1) + len(list2)
    result = [0] * result_length
    
    for i in reversed(range(len(list1))):
        carry = 0
        for j in reversed(range(len(list2))):
            temp = list1[i] * list2[j] + carry
            carry, digit = divmod(result[i+j+1] + temp, 2)
            result[i+j+1] = digit
        result[i] += carry
    
    sign = list1[0] ^ list2[0]
    result = [sign] + result
    
    while len(result) > 1 and result[0] == 0:
        result = result[1:]
    
    result = [str(bit) for bit in result]
    
    while len(result) < result_length+1:
        result.insert(0, '0')
    
    result = [int(bit) for bit in result]
    return result

def binary_division(dividend, divisor):
    flag = True
    if dividend[0] == 1 or divisor[0] == 1:
        flag = False
    if not all(bit in (0, 1) for bit in dividend[1:] + divisor[1:]):
        return None

    dividend_int = int(''.join(str(bit) for bit in dividend[1:]), 2)
    divisor_int = int(''.join(str(bit) for bit in divisor[1:]), 2)

    if divisor_int == 0:
        return None
    
    quotient_int = dividend_int // divisor_int
    quotient_bin = bin(quotient_int)[2:]
    
    quotient = [int(bit) for bit in quotient_bin]
    while len(quotient) < len(dividend) - len(divisor) + 1:
        quotient.insert(0, 0)
        
    if flag == False:
        quotient = [1 if bit == 0 else 0 for bit in quotient]
    quotient.insert(0,0)
    return quotient


def from_decimal_to_float(decimal):
    if "1" in decimal[:decimal.index(".")]:
        exp_sign = 1
    else:
        exp_sign = -1
    sign_bit = [0]
    if decimal.index("1", 0, decimal.index(".")) == -1:
        exp_bits = decimal_to_binary_direct_order(exponent_constant + (
            (decimal.index("1") - decimal.index(".")) * exp_sign))[-8:]
    else:
        exp_bits = decimal_to_binary_direct_order(exponent_constant + (
            (decimal.index(".") - decimal.index("1") - 1) * exp_sign))[-8:]
    decimal = decimal[:decimal.index(".")] + decimal[decimal.index(".") + 1:]
    mantissa = decimal[decimal.index("1") + 1:]
    result = sign_bit + [int(b) for b in exp_bits] + [int(b) for b in mantissa]
    print("float_form =" + str(result))
    return result



def _to_fix(decimal):
    if decimal == 0:
        return [0] * 24
    temp1 = int(decimal)
    i = 0
    mantissa_size = 23
    fraction_part = decimal - float(temp1)
    temp2 = decimal_to_binary_additional_order(temp1)
    if temp2.count(1) == 0:
        result = [0]
    else:
        result = temp2[temp2.index(1):]
    result.append(".")
    while i <= (mantissa_size - len(result)):
        fraction_part *= 2
        if int(fraction_part) == 0:
            result.append(0)
        elif int(fraction_part) == 1:
            fraction_part -= 1
            result.append(1)
            if fraction_part == 0:
                result += [0] * (23 - len(result) + 1)
    print(result,"to fix1")
    return result

def list_to_string(list):
   return ''.join(str(elem) for elem in list)

def summ_of_floating(decimal1, decimal2):
    decimal1 = _to_fix(decimal1)
    decimal2 = _to_fix(decimal2)
    decimal1 = list_to_string(decimal1)
    decimal2 = list_to_string(decimal2)
    unitnum1 = decimal1.find("1", 0, decimal1.find("."))
    unitnum2 = decimal2.find("1", 0, decimal2.find("."))
    exp1 = decimal1.find(".") - unitnum1 - 1
    exp2 = decimal2.find(".") - unitnum2 - 1
    if decimal1.find("1", 0, decimal1.find(".")) == -1:
        exp1 = 0
    if decimal2.find("1", 0, decimal2.find(".")) == -1:
        exp2 = 0
    if exp1 >= exp2:
        diff_exp = exp1 - exp2
        numsumm2 = "0" * diff_exp + decimal2[:(decimal2.find("."))] + decimal2[
            (decimal2.find(".") + 1):(len(decimal2) - diff_exp)]
        numsumm1 = decimal1[:(decimal1.find("."))] + decimal1[(decimal1.find(".") + 1):]
    else:
        diff_exp = exp2 - exp1
        numsumm1 = "0" * diff_exp + decimal1[:(decimal1.find("."))] + decimal1[
            (decimal1.find(".") + 1):(len(decimal1) - diff_exp)]
        numsumm2 = decimal2[:(decimal2.find("."))] + decimal2[(decimal2.find(".") + 1):]
    temp_floating_summ = sum_of_binary_numbers(numsumm1, numsumm2)
    temp_floating_summ = list_to_string(temp_floating_summ)
    add_numbers = len(temp_floating_summ) - len(numsumm2)
    result = temp_floating_summ[:(max(decimal1.find("."), decimal2.find("."))) + add_numbers] + "." + \
             temp_floating_summ[(max(exp1, exp2) + add_numbers + 1):]
    result = from_decimal_to_float(result)
    return result

def from_float_to_decimal(float_number):
    if float_number[0] == 0:
        sign = 1
    else:
        sign = -1
    exp = 0
    for i in range(1, 9):
        exp += float_number[i] * (2 ** (8 - i))
    exp -= 127
    frac = 0
    for i in range(9, 32):
        frac += float_number[i] * (2 ** (-(i - 8)))
    result = sign * (1 + frac) * (2 ** exp)
    return result




def binary_to_decimal_normal(binary):
    decimal = 0
    sign = 1
    if binary[0] == 1:
        sign = -1
        binary = binary[1:]
    for digit in binary:
        decimal = decimal * 2 + digit
    return sign * decimal

def if_number_is_negative(context):
    answerinreverse = from_additional_to_reverse(context)
    answerindirect = from_reverse_to_direct(answerinreverse)
    result = binary_to_decimal_normal(answerindirect)
    print(result)
    return result

def from_binary_to_decimal(binary_number):
    result_int = 0
    binary_list = [int(x) for x in binary_number]
    if binary_list[0] == 1:
        result_int += ((-binary_list[1]) * pow(2, (len(binary_list) - 2)))
        for i in range(2, len(binary_list)):
            result_int += ((binary_list[i]) * pow(2, (len(binary_list) - (i + 1))))
    elif binary_list[0] == 0:
        for i in range(0, len(binary_list)):
            result_int += (binary_list[i] * pow(2, (len(binary_list) - (i + 1))))
    return result_int



def number_code_check(decimal):
    if decimal > 0:
        decimal = decimal_to_binary_direct_order(decimal)
    else:
        decimal = decimal_to_binary_additional_order(decimal)
    return decimal


def type_of_operation(numberr1, numberr2, command_of_operation):
    match command_of_operation:
        case 1:
            pass
        case 2:
            numberr2 = -numberr2
        case 3:
            numberr1 = abs(numberr1)
            numberr2 = abs(numberr2)
        case 4:
            numberr1 = abs(numberr1)
            numberr2 = abs(numberr2)
            if (numberr1 == 0) | (numberr2 == 0):
                numberr1 = 0
                numberr2 = 0
            if numberr1 < numberr2:
                numberr1, numberr2 = numberr2, numberr1
    return numberr1, numberr2, command_of_operation

def int_or_float(num):
    if "." in num:
        result = float(num)
    else:
        result = int(num)
    return result


def menu():
    while True:
        numberr1 = (input("Enter the first number:"))
        numberr2 = (input("Enter the second number:"))
        numberr1 = int_or_float(numberr1)
        numberr2 = int_or_float(numberr2)
        number1,number2 = "0","0"
        operation_command = int(input("Выберите операцию: (1 — Сумма \n  2 — Разность \n  3 — Умножение \n  4 — Деление \n  5 — Сумма вещественных чисел \n "))

        numberr1, numberr2, operation_command = type_of_operation(numberr1, numberr2, operation_command)

        command = int(input("Выберите типы кодов (1 — Прямой и обратный \n 2 — Прямой и дополнительный \n , 3 — Дополнительный и обратный \n "
                            "4 — Для вещественных чисел \n"))
        match command:
            case 1:
                if numberr1 < 0 < numberr2:
                    temp = numberr1
                    numberr1 = numberr2
                    numberr2 = temp
                number1 = decimal_to_binary_direct_order(numberr1)
                number2 = decimal_to_binary_reverse_order(numberr2)
                print("first_number = ", decimal_to_binary_direct_order(numberr1))
                print("second_number = ", decimal_to_binary_additional_order(numberr2))
            case 2:
                if numberr1 < 0 < numberr2:
                    temp = numberr1
                    numberr1 = numberr2
                    numberr2 = temp
                number1 = decimal_to_binary_direct_order(numberr1)
                number2 = decimal_to_binary_additional_order(numberr2)
                print("first_number = ", decimal_to_binary_direct_order(numberr1))
                print("second_number = ", decimal_to_binary_additional_order(numberr2))
            case 3:
                number1 = decimal_to_binary_additional_order(numberr1)
                number2 = decimal_to_binary_additional_order(numberr2)
                print("first_number = ", decimal_to_binary_additional_order(numberr1))
                print("second_number = ", decimal_to_binary_additional_order(numberr2))
            case 4:
                pass

        match operation_command:
            case 1 | 2:
                print("Сумма/Разность = " + (str(from_binary_to_decimal(sum_of_binary_numbers(number1, number2)))))
            case 3:
                number1, number2 = (length_comparison(number1, number2))
                print("Умножение = " + str(from_binary_to_decimal(binary_multiplication(number1, number2))))
            case 4:
                number1, number2 = (length_comparison(number1, number2))
                print("Деление = " + str(from_binary_to_decimal(binary_division(number1, number2))))
            case 5:
                print("Сумма вещественных  = " + str(from_float_to_decimal(summ_of_floating(numberr1, numberr2))))

if __name__ == "__main__":
   menu() 
    