import random

def generate_simple_fio(num_rows=1000):
    """
    Простой генератор только ФИО
    """
    first_names = ['Александр', 'Алексей', 'Андрей', 'Анна', 'Мария', 'Елена', 
                   'Дмитрий', 'Сергей', 'Иван', 'Ольга', 'Наталья', 'Михаил']
    
    last_names = ['Иванов', 'Петров', 'Сидоров', 'Смирнов', 'Кузнецов', 'Попов']
    
    middle_names = ['Александрович', 'Алексеевич', 'Андреевич', 'Сергеевич', 
                   'Дмитриевич', 'Иванович', 'Александровна', 'Алексеевна', 
                   'Андреевна', 'Сергеевна', 'Дмитриевна', 'Ивановна']
    
    data = []
    
    for i in range(num_rows):
        first_name = random.choice(first_names)
        last_name = random.choice(last_names)
        middle_name = random.choice(middle_names)
        
        data.append(f"{last_name} {first_name} {middle_name}")
    
    return data

# Генерация и сохранение простых данных
simple_data = generate_simple_fio(1000)

with open('lexicographic.txt', 'w', encoding='utf-8') as f:
    for line in simple_data:
        f.write(line + '\n')

print("Простые данные сохранены в 'simple_fio_1000.txt'")
print("Первые 10 строк:")
for i in range(10):
    print(simple_data[i])