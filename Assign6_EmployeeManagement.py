class Employee:
    def __init__(self):
        self.criteria={
            "Punctuality":0,
            "Quality of Work":0,
            "Teamwork":0,
            "Communication":0,
            "Task Completion":0
        }
        self.name=""
        self.id=""
        self.total_score=0
    def input(self):
        self.name = input("Enter the name of the employee: ")
        self.id = input("Enter the ID of the employee: ")
        print(f"\nEvaluating {self.name} (ID: {self.id})")
        print("Enter the score between 1 to 10 for each criterion:")
        self.total_score=0
        for i in self.criteria:
            while True:
                score=int(input(f"{i}:"))
                if(score>=1 and score<=10):
                    self.criteria[i]=score
                    self.total_score+=score
                    break
                else:
                    print("Enter score between 1 to 10")
        return self.total_score          
    def evaluate(self,total_score):
        if(total_score>=42):
            return "Excellent","Eligible for promotion"
        elif(total_score>=35):
            return "Good","Consider recognition"
        else:
            return "Needs Improvement","Recommend training"
    def display(self, total_score):
        print("\n📊 Evaluation Results")
        print(f"  Employee Name : {self.name}")
        print(f"  Employee ID   : {self.id}")
        print(f"  Total Score   : {self.total_score}")
        level, advice = self.evaluate(self.total_score)
        print(f"  Performance   : {level}")
        print(f"  Suggestion    : {advice}")
        print("-" * 40)
emp_list=[]        
emp=int(input("Enter the number of employees you want to evaluate"))
for i in range(emp):
    e=Employee()
    score=e.input()
    e.display(score)
    emp_list.append(e)
max_score=0
for i in emp_list:
    max_score=max(max_score,i.total_score)
best_employees=[]
for i in emp_list:
    if(max_score==i.total_score):
        best_employees.append(i)
print(f"Following are the best employee with score{max_score}")
for i in best_employees:
    print(f"Best Empoloyee is:{i.name}")        
    
