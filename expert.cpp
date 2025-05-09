#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
class Employee {
public:
    map<string, int> criteria; // Criterion -> score
    string name;
    string id;
    int total_score;

    // Constructor to initialize criteria
    Employee() : total_score(0) {
        criteria = {
            {"Punctuality", 0},
            {"Quality of Work", 0},
            {"Teamwork", 0},
            {"Communication", 0},
            {"Task Completion", 0}
        };
    }

    // Input employee details and scores
    void input() {
        cout << "\n===============================\n";
        cout << "📥 Enter details for new employee\n";
        cout << "Name: ";
        cin >> ws; // To consume leading whitespace
        getline(cin, name);
        cout << "ID: ";
        getline(cin, id);

        cout << "\nEvaluating " << name << " (ID: " << id << ")\n";
        total_score = 0;

        for (auto& criterion : criteria) {
            int score;
            while (true) {
                cout << "Enter score (1-10) for " << criterion.first << ": ";
                cin >> score;
                if (score >= 1 && score <= 10) {
                    criterion.second = score;
                    total_score += score;
                    break;
                } else {
                    cout << "❗ Invalid score. Please enter between 1 to 10.\n";
                }
            }
        }
    }

    // Expert system logic for performance evaluation
    pair<string, string> evaluate() {
        // Knowledge-based inference rules
        if (total_score >= 45) {
            return {"🌟 Outstanding", "Strongly recommend promotion and leadership roles"};
        } else if (total_score >= 38) {
            return {"👍 Good", "Eligible for bonus or recognition"};
        } else if (total_score >= 30) {
            return {"🛠 Needs Improvement", "Enroll in upskilling programs"};
        } else {
            return {"⚠ Critical", "Schedule performance review and mentorship"};
        }
    }
    

    // Generate specific advice based on weak criteria
    vector<string> expertAdvice() {
        vector<string> suggestions;
        for (const auto& [key, val] : criteria) {
            if (val < 5) {
                suggestions.push_back("Improve " + key + " (scored " + to_string(val) + ")");
            }
        }
        return suggestions;
    }

    // Display results
    void display() {
        cout << "\n📊 Evaluation Summary\n";
        cout << "Name          : " << name << endl;
        cout << "ID            : " << id << endl;
        cout << "Total Score   : " << total_score << " / 50" << endl;

        auto [performance, suggestion] = evaluate();
        cout << "Performance   : " << performance << endl;
        cout << "System Advice : " << suggestion << endl;

        auto adviceList = expertAdvice();
        if (!adviceList.empty()) {
            cout << "⚙ Expert Suggestions:\n";
            for (const auto& advice : adviceList) {
                cout << "  - " << advice << endl;
            }
        }
        cout << string(40, '-') << endl;
    }
};

int main() {
    vector<Employee> emp_list;
    int n;

    cout << "👔 Welcome to the Employee Evaluation Expert System\n";
    cout << "Enter number of employees to evaluate: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        Employee e;
        e.input();
        e.display();
        emp_list.push_back(e);
    }

    // Identify top scorer(s)
    int max_score = 0;
    for (const auto& e : emp_list) {
        if (e.total_score > max_score) {
            max_score = e.total_score;
        }
    }

    cout << "\n🏅 Top Performers (Score: " << max_score << ")\n";
    for (const auto& e : emp_list) {
        if (e.total_score == max_score) {
            cout << " - " << e.name << " (ID: " << e.id << ")\n";
        }
    }

    return 0;
}
