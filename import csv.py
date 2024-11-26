import csv
import random

# Define the range for BaseSalary
salary_range = (40000, 120000)

# Define the range for each percentage
percentage_range = {
    'HRPercent': (10, 25),
    'TRPercent': (10, 20),
    'OtherPercent': (5, 15),
    'PFPercent': (8, 15),
    'ITPercent': (3, 8),
}

# Generate names for employees
first_names = ["John", "Jane", "Alex", "Emily", "Michael", "Sarah", "David", "Laura", "Chris", "Anna"]
last_names = ["Doe", "Smith", "Johnson", "Brown", "Williams", "Jones", "Davis", "Miller", "Wilson", "Taylor"]

def generate_employee_name():
    return f"{random.choice(first_names)} {random.choice(last_names)}"

# Generate the employee data
employees = []
for _ in range(2000):
    name = generate_employee_name()
    base_salary = random.randint(*salary_range)
    hr_percent = random.randint(*percentage_range['HRPercent'])
    tr_percent = random.randint(*percentage_range['TRPercent'])
    other_percent = random.randint(*percentage_range['OtherPercent'])
    pf_percent = random.randint(*percentage_range['PFPercent'])
    it_percent = random.randint(*percentage_range['ITPercent'])
    
    employees.append([name, base_salary, hr_percent, tr_percent, other_percent, pf_percent, it_percent])

# Write the data to a CSV file
filename = 'employees3.csv'
header = ["Name", "BaseSalary", "HRPercent", "TRPercent", "OtherPercent", "PFPercent", "ITPercent"]

with open(filename, 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(header)
    writer.writerows(employees)

print(f"CSV file '{filename}' has been created with 2000 employees data.")
