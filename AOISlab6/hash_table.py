from copy import deepcopy

class HashTable_element:
    def __init__(self, key, value):
        self.key = key
        self.value = value

class Hash_Table:
    def __init__(self):
        self.TABLE_SIZE = 25
        self.TABLE_LINE_SIZE = 4
        self.HASH_FUNC_CONST = 127
        self.HASH_TABLE = [[] for _ in range(self.TABLE_SIZE)]

    def hash_func(self, input):
        hash_table_element = HashTable_element(input[0], input[1])
        hash_word = [i for i in hash_table_element.key]
        ready_hash = ord(hash_word[0]) * self.HASH_FUNC_CONST
        ready_hash += ord(hash_word[1])
        for i in map(ord, hash_word[2:]):
            ready_hash *= self.HASH_FUNC_CONST
            ready_hash += i
        ready_hash %= self.TABLE_SIZE
        return (ready_hash, hash_table_element)

    def add_hash_line(self, input):
        index_of_hash, key_value = self.hash_func(input)
        for i in range(len(self.HASH_TABLE[index_of_hash])):
            if self.HASH_TABLE[index_of_hash][i].key == key_value.key:
                self.HASH_TABLE[index_of_hash][i].value = key_value.value
                break
        else:
            self.HASH_TABLE[index_of_hash].append(key_value)

        if self.looking_for_overflow():
            self.print_table()
            self.print_new_table()
            print('NEW TABLE')
            self.rebuild_table()

    def print_table(self):
        print("{:<5} {:<10} {:<10}".format('ID', 'KEY', 'VALUE'))
        for i in range(len(self.HASH_TABLE)):
            for j in range(0, len(self.HASH_TABLE[i])):
                print("{:<5} {:<10} {:<10}".format(i, self.HASH_TABLE[i][j].key,self.HASH_TABLE[i][j].value))
            if len(self.HASH_TABLE[i]) == 0:
                print("{:<5} {:<10} {:<10}".format(i, '', ''))

    def print_new_table(self):
        for i in range(len(self.HASH_TABLE)):
            print(f'[{i}]', end=' : ')
            for j in range(0, len(self.HASH_TABLE[i])):
                if j != len(self.HASH_TABLE[i]) - 1:
                    print(f'{self.HASH_TABLE[i][j].key}:{self.HASH_TABLE[i][j].value}', end=' -> ')
                else:
                    print(f'{self.HASH_TABLE[i][j].key}:{self.HASH_TABLE[i][j].value}', end=' ')
            print('\n')

    def looking_for_overflow(self):
        for i in self.HASH_TABLE:
            if not i:
                return False
        return True

    def delete_element(self, input):
        hash_key, elements = self.hash_func([input, ''])
        for i in self.HASH_TABLE[hash_key]:
            if i.key == input:
                self.HASH_TABLE[hash_key].remove(i)

    def search_for_element(self, key):
        hash_key, _ = self.hash_func([key, ''])
        for i in self.HASH_TABLE[hash_key]:
            if i.key == key:
                print(i.value)
                break

    def rebuild_table(self):
        temp_hash_table = deepcopy(self.HASH_TABLE)
        self.TABLE_SIZE *= 2
        self.HASH_TABLE = [[] for _ in range(self.TABLE_SIZE)]

        for i in temp_hash_table:
            for j in i:
                self.add_hash_line([j.key, j.value])