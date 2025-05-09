#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <limits>

using namespace std;

// Simple Employee Performance Evaluation System

class EmployeeSystem {
public:
    // Data structures using simple structs instead of classes
    struct Employee {
        string id;
        string name;
        string position;
        string department;
        map<string, int> scores;       // Criterion name -> score
        map<string, string> comments;  // Criterion name -> comment
    };
    // Main data
    vector<Employee> employees;
    map<string, double> criteria_weights;  // Criterion name -> weight
    map<string, string> criteria_desc;     // Criterion name -> description

    // Initialize the system with default criteria
    void init() {
        // Add default criteria
        criteria_weights["Productivity"] = 0.25;
        criteria_desc["Productivity"] = "Work output and efficiency";
        
        criteria_weights["Quality"] = 0.25;
        criteria_desc["Quality"] = "Accuracy and thoroughness of work";
        
        criteria_weights["Communication"] = 0.15;
        criteria_desc["Communication"] = "Effectiveness in verbal and written communications";
        
        criteria_weights["Team Collaboration"] = 0.15;
        criteria_desc["Team Collaboration"] = "Ability to work effectively with others";
        
        criteria_weights["Initiative"] = 0.20;
        criteria_desc["Initiative"] = "Self-direction and proactive problem-solving";
    }
    
    // Add a new employee
    void addEmployee(string id, string name, string position, string department) {
        Employee emp;
        emp.id = id;
        emp.name = name;
        emp.position = position;
        emp.department = department;
        employees.push_back(emp);
    }
    
    // Rate an employee on a criterion
    void rateEmployee(string emp_id, string criterion, int score, string comment) {
        if (score < 1 || score > 5) {
            cout << "Error: Score must be between 1 and 5" << endl;
            return;
        }
        
        // Find the employee
        for (auto& emp : employees) {
            if (emp.id == emp_id) {
                emp.scores[criterion] = score;
                emp.comments[criterion] = comment;
                return;
            }
        }
        
        cout << "Error: Employee not found" << endl;
    }
    
    // Calculate overall score for an employee
    double calculateOverallScore(string emp_id) {
        for (auto& emp : employees) {
            if (emp.id == emp_id) {
                double overall = 0.0;
                double weight_sum = 0.0;
                
                for (auto& criterion : criteria_weights) {
                    string crit_name = criterion.first;
                    double weight = criterion.second;
                    
                    if (emp.scores.find(crit_name) != emp.scores.end()) {
                        overall += emp.scores[crit_name] * weight;
                        weight_sum += weight;
                    }
                }
                
                if (weight_sum > 0) {
                    return overall / weight_sum;
                }
                return 0.0;
            }
        }
        return 0.0;
    }
    
    // Get performance tier based on score
    string getPerformanceTier(double score) {
        if (score >= 4.5) return "Outstanding";
        if (score >= 3.5) return "Exceeds Expectations";
        if (score >= 2.5) return "Meets Expectations";
        if (score >= 1.5) return "Needs Improvement";
        return "Unsatisfactory";
    }
    
    // Get feedback based on criterion and score
    string getFeedback(string criterion, int score) {
        if (criterion == "Productivity") {
            switch (score) {
                case 1: return "Shows significant difficulty meeting basic productivity expectations.";
                case 2: return "Often falls below expectations in terms of work output.";
                case 3: return "Meets standard productivity requirements consistently.";
                case 4: return "Frequently exceeds productivity expectations.";
                case 5: return "Demonstrates exceptional productivity that consistently exceeds expectations.";
            }
        } else if (criterion == "Quality") {
            switch (score) {
                case 1: return "Work frequently contains errors and requires substantial rework.";
                case 2: return "Work sometimes meets quality standards but improvement is needed.";
                case 3: return "Consistently delivers work that meets quality standards.";
                case 4: return "Produces high-quality work with minimal errors.";
                case 5: return "Delivers outstanding quality work that can serve as a benchmark for others.";
            }
        } else if (criterion == "Communication") {
            switch (score) {
                case 1: return "Shows significant difficulties in communication that impact work effectiveness.";
                case 2: return "Communication is sometimes unclear or ineffective.";
                case 3: return "Communicates adequately with colleagues and stakeholders.";
                case 4: return "Demonstrates strong communication skills that enhance team dynamics.";
                case 5: return "Exceptional communicator who excels at conveying complex information.";
            }
        } else if (criterion == "Team Collaboration") {
            switch (score) {
                case 1: return "Has difficulty working effectively with team members.";
                case 2: return "Sometimes collaborates effectively but improvement is needed.";
                case 3: return "Works well with team members to achieve shared goals.";
                case 4: return "Frequently enhances team dynamics and helps others succeed.";
                case 5: return "Exceptional team player who significantly elevates team performance.";
            }
        } else if (criterion == "Initiative") {
            switch (score) {
                case 1: return "Rarely demonstrates initiative and requires constant direction.";
                case 2: return "Occasionally shows initiative but often waits for instructions.";
                case 3: return "Shows appropriate initiative in daily responsibilities.";
                case 4: return "Frequently identifies and acts on opportunities for improvement.";
                case 5: return "Demonstrates exceptional initiative that creates significant value.";
            }
        }
        return "No feedback available.";
    }
    
    // Get improvement suggestion based on criterion and score
    string getImprovement(string criterion, int score) {
        if (criterion == "Productivity") {
            switch (score) {
                case 1: return "Consider time management training and breaking tasks into smaller goals.";
                case 2: return "Identify productivity bottlenecks. Try timeboxing and prioritization methods.";
                case 3: return "Continue meeting expectations while looking for efficiency improvements.";
                case 4: return "Share productivity techniques with team members. Look for automation opportunities.";
                case 5: return "Consider mentoring others on productivity. Balance workload to maintain quality.";
            }
        } else if (criterion == "Quality") {
            switch (score) {
                case 1: return "Implement a personal quality checklist. Seek frequent feedback during work.";
                case 2: return "Establish review procedures before submission. Allocate more time for quality checks.";
                case 3: return "Document successful processes to ensure consistency. Consider peer reviews.";
                case 4: return "Look for opportunities to establish quality standards for others.";
                case 5: return "Share quality assurance techniques with the team. Consider leading quality initiatives.";
            }
        } else if (criterion == "Communication") {
            switch (score) {
                case 1: return "Consider communication skills training. Practice active listening and seek feedback.";
                case 2: return "Prepare key points before communications. Ask clarifying questions more frequently.";
                case 3: return "Continue developing skills by seeking opportunities to present and facilitate discussions.";
                case 4: return "Share communication best practices with team members. Consider leading presentations.";
                case 5: return "Consider mentoring others in effective communication.";
            }
        } else if (criterion == "Team Collaboration") {
            switch (score) {
                case 1: return "Schedule regular check-ins with team members. Actively seek ways to support team goals.";
                case 2: return "Improve collaboration by actively participating and offering assistance.";
                case 3: return "Continue fostering positive team relationships. Align individual and team goals.";
                case 4: return "Share collaboration techniques with team members.Consider team building activities.";
                case 5: return "Continue exemplary collaboration while developing team members' collaborative skills.";
            }
        } else if (criterion == "Initiative") {
            switch (score) {
                case 1: return "Start by identifying one area where you can take more initiative.";
                case 2: return "Look for opportunities to suggest improvements. Take ownership of smaller projects.";
                case 3: return "Continue showing initiative while identifying higher-impact areas for improvement.";
                case 4: return "Look for strategic initiatives that align with department goals.";
                case 5: return "Continue exceptional initiative while developing leadership skills.";
            }
        }
        return "No specific improvement suggestions available.";
    }


    // Print list of all employees
    void listEmployees() {
        cout << "\n===== EMPLOYEE LIST =====" << endl;
        for (auto& emp : employees) {
            cout << "ID: " << emp.id << " | Name: " << emp.name << " | Position: " << emp.position << endl;
        }
        cout << "=========================" << endl;
    }
    
    // Generate and print evaluation report for an employee
    void generateReport(string emp_id) {
        // Find the employee
        bool found = false;
        Employee emp;
        
        for (auto& e : employees) {
            if (e.id == emp_id) {
                emp = e;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Error: Employee not found" << endl;
            return;
        }
        
        double overall = calculateOverallScore(emp_id);
        string tier = getPerformanceTier(overall);
        
        cout << "\n=============================================================" << endl;
        cout << "             PERFORMANCE EVALUATION REPORT                   " << endl;
        cout << "=============================================================" << endl;
        cout << "Employee ID: " << emp.id << endl;
        cout << "Name: " << emp.name << endl;
        cout << "Position: " << emp.position << endl;
        cout << "Department: " << emp.department << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "PERFORMANCE RATINGS:" << endl;
        cout << "-------------------------------------------------------------" << endl;
        
        for (auto& crit : criteria_weights) {
            string name = crit.first;
            double weight = crit.second;
            
            if (emp.scores.find(name) != emp.scores.end()) {
                int score = emp.scores[name];
                string comment = emp.comments[name];
                
                cout << name << " (" << weight * 100 << "%): " << score << "/5" << endl;
                cout << "Comment: " << comment << endl;
                cout << "Feedback: " << getFeedback(name, score) << endl;
                cout << "Improvement: " << getImprovement(name, score) << endl;
                cout << endl;
            }
        }
        
        cout << "-------------------------------------------------------------" << endl;
        cout << "OVERALL ASSESSMENT:" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Overall Rating: " << fixed << setprecision(2) << overall << "/5.00" << endl;
        cout << "Performance Tier: " << tier << endl;
        cout << "=============================================================" << endl;
    }
};

int main() {
    EmployeeSystem system;
    
    system.init();
    
    // Add some sample employees
    system.addEmployee("E001", "Alice", "Software Engineer", "Development");
    system.addEmployee("E002", "Bob", "Data Scientist", "Data");
    
    // Example of rating employees
    system.rateEmployee("E001", "Productivity", 4, "Consistently meets deadlines.");
    system.rateEmployee("E001", "Quality", 5, "Work quality is always excellent.");
    system.rateEmployee("E002", "Communication", 3, "Communicates effectively but room for improvement.");
    
    // Generate reports
    system.generateReport("E001");
    system.generateReport("E002");
    
    return 0;
}
