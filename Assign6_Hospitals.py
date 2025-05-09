class MedicalExpertSystem:
    def __init__(self):
        self.conditions = {
            "Cardiologist": {
                "symptoms": {
                    "chest pain": 3,
                    "high blood pressure": 3,
                    "irregular heartbeat": 3,
                    "shortness of breath": 3,
                    "fatigue": 2,
                    "dizziness": 2,
                    "swelling in legs": 2,
                    "cold sweats": 3
                },
                "risk_factors": ["smoking", "diabetes", "high cholesterol", "obesity"],
                "advice": "Consult a cardiologist for heart health. Maintain a low-sodium diet, exercise regularly, and monitor blood pressure."
            },
            "Pulmonologist": {
                "symptoms": {
                    "shortness of breath": 3,
                    "persistent cough": 3,
                    "asthma": 3,
                    "wheezing": 3,
                    "chronic bronchitis": 3,
                    "chest tightness": 3,
                    "coughing up blood": 4
                },
                "risk_factors": ["smoking", "air pollution exposure", "family history of lung disease"],
                "advice": "Visit a pulmonologist. Avoid smoke and allergens, and consider a lung function test."
            },
            "Neurologist": {
                "symptoms": {
                    "severe headache": 3,
                    "dizziness": 3,
                    "memory loss": 4,
                    "numbness": 3,
                    "migraine": 3,
                    "seizures": 4,
                    "vision disturbances": 3
                },
                "risk_factors": ["stroke history", "brain injury", "chronic migraines"],
                "advice": "Consult a neurologist. Ensure proper hydration, sleep, and stress management."
            },
            "Orthopedic": {
                "symptoms": {
                    "joint pain": 3,
                    "back pain": 3,
                    "bone fracture": 4,
                    "knee pain": 3,
                    "stiffness": 2,
                    "swollen joints": 3,
                    "difficulty walking": 3
                },
                "risk_factors": ["osteoporosis", "previous fractures", "high-impact sports"],
                "advice": "Visit an orthopedic doctor. Maintain calcium intake and avoid excessive strain on joints."
            },
            "Endocrinologist": {
                "symptoms": {
                    "frequent urination": 3,
                    "unexplained weight loss": 3,
                    "excessive thirst": 3,
                    "hormonal imbalance": 3,
                    "irregular periods": 3,
                    "hair loss": 2,
                    "extreme fatigue": 3
                },
                "risk_factors": ["diabetes", "thyroid disorders", "polycystic ovary syndrome"],
                "advice": "Consult an endocrinologist. Monitor blood sugar and hormone levels regularly."
            },
            "General Physician": {
                "symptoms": {
                    "fever": 2,
                    "body ache": 2,
                    "fatigue": 2,
                    "weakness": 2,
                    "mild headache": 2,
                    "sore throat": 2,
                    "cough": 2
                },
                "risk_factors": [],
                "advice": "See a general physician. Stay hydrated and rest well."
            },
        }

        self.severity_levels = {
            "mild": "Monitor your symptoms and take rest. If they persist, consult a doctor.",
            "moderate": "Consider booking an appointment soon for a check-up.",
            "severe": "Seek immediate medical attention as the condition may require urgent care."
        }

        # Indian doctors and cities
        self.specialist_database = {
            "Mumbai": {
                "Cardiologist": ["Dr. Rajesh Shah - Fortis Mumbai", "Dr. Pooja Mehta - Lilavati Hospital"],
                "Pulmonologist": ["Dr. Anil Deshmukh - Breather's Care Mumbai", "Dr. Nisha Agarwal - Hinduja Hospital"],
                "Neurologist": ["Dr. Suresh Patil - NeuroCare Mumbai", "Dr. Sneha Iyer - Kokilaben Hospital"]
            },
            "Delhi": {
                "Cardiologist": ["Dr. Ramesh Gupta - AIIMS Delhi", "Dr. Alok Verma - Max Hospital"],
                "Orthopedic": ["Dr. Vikram Ahuja - Apollo Delhi", "Dr. Anjali Sharma - Medanta Delhi"],
                "Endocrinologist": ["Dr. Manish Tandon - BLK Hospital", "Dr. Neha Kapoor - Fortis Delhi"]
            },
            "Bangalore": {
                "Pulmonologist": ["Dr. Ravi Kumar - Manipal Bangalore", "Dr. Sunita Rao - Columbia Asia"],
                "Neurologist": ["Dr. Arvind Menon - NIMHANS", "Dr. Lakshmi Reddy - Sakra Hospital"]
            },
            "Hyderabad": {
                "Cardiologist": ["Dr. Srikanth Reddy - Yashoda Hyderabad", "Dr. Kavita Jain - Apollo Hyderabad"],
                "Orthopedic": ["Dr. Aditya Sharma - Sunshine Hospital", "Dr. Priya Desai - Care Hospital"]
            },
            "Chennai": {
                "Pulmonologist": ["Dr. Mohan Babu - Global Hospitals", "Dr. Sangeeta Narayan - MGM Healthcare"],
                "Neurologist": ["Dr. Karthik Balaji - SIMS Hospital", "Dr. Anuradha Iyengar - Fortis Chennai"]
            }
        }    
    def get_specialists(self, symptoms, risk_factors):
        specialist_scores = {}

        for specialist, details in self.conditions.items():
            score = 0
            matched_symptoms = []
            matched_risks = list(set(risk_factors) & set(details["risk_factors"]))

            for symptom in symptoms:
                if symptom in details["symptoms"]:
                    score += details["symptoms"][symptom]
                    matched_symptoms.append(symptom)

            if matched_risks:
                score += len(matched_risks)

            if score > 0:
                specialist_scores[specialist] = {
                    "score": score,
                    "matched_symptoms": matched_symptoms,
                    "matched_risks": matched_risks,
                    "advice": details["advice"]
                }

        return specialist_scores

    def determine_severity(self, total_score):
        if total_score <= 4:
            return "mild"
        elif 5 <= total_score <= 8:
            return "moderate"
        else:
            return "severe"

    def find_fixed_nearby_specialists(self, specialist_type, location):
        city_specialists = self.specialist_database.get(location, {})
        return city_specialists.get(specialist_type, ["No available specialists found in this location."])

    def run_system(self):
        print("\n🏥 Welcome to the Indian Medical Expert System!")
        print("Enter your symptoms separated by commas (e.g., chest pain, dizziness, fatigue):")
        user_symptoms = input().strip().lower().split(",")
    
        print("\nEnter risk factors (if any) separated by commas:")
        user_risks = input().strip().lower().split(",")
        symptoms = user_symptoms  
        risk_factors = user_risks  

        specialists = self.get_specialists(symptoms, risk_factors)
        total_score = sum(details["score"] for details in specialists.values())
        severity_level = self.determine_severity(total_score)

        if specialists:
            for specialist, details in sorted(specialists.items(), key=lambda x: x[1]['score'], reverse=True):
                print(f"\n✅ {specialist} - {details['advice']}")
                location = input(f"\n📍 Enter your city to find {specialist}s nearby: ").strip()
                print(f"\n🏥 Nearby {specialist}s in {location}: {', '.join(self.find_fixed_nearby_specialists(specialist, location))}")

            print(f"\n⚠️ Severity Level: {severity_level.capitalize()} - {self.severity_levels[severity_level]}")
        else:
            print("\n⚠️ No specialist detected. Visit a General Physician first.")

if __name__ == "__main__":
    system = MedicalExpertSystem()
    system.run_system()


