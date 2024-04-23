#include <iostream>
#include <cstring>
#define MAX 10000
using namespace std;

struct queue {
    char queue_array[MAX] = "\0";
    int front_queue = -1;
    int tail_queue = -1;
    queue() { };
};

void pop_queue(queue* edit) {
    edit->front_queue++;
}

void push_queue(queue* edit, char to_push) {
    edit->tail_queue++;
    edit->queue_array[edit->tail_queue] = to_push;
}

void clear_queue(queue* edit) {
    memset(edit->queue_array, '\0', sizeof(edit->queue_array));
}

bool is_empty_queue(queue* edit) {
    return edit->front_queue == edit->tail_queue;
}

void show_queue(queue* edit) {
    for (int i = edit->front_queue + 1; i <= edit->tail_queue; i++) {
        cout << edit->queue_array[i] << " ";
    }
    cout << "\n";
}

struct stack {
    char stack_array[MAX] = "\0";
    int top_stack = -1;
    stack() { }
};

void pop_stack(stack* edit) {
    edit->top_stack--;
}

void push_stack(stack* edit, char to_push) {
    edit->top_stack++;
    edit->stack_array[edit->top_stack] = to_push;
}

bool is_empty_stack(stack* edit) {
    return edit->top_stack == -1;
}

void clear_stack(stack* edit) {
    memset(edit->stack_array, 0, sizeof(edit->stack_array));
}

char top_stack(stack* edit) {
    return edit->stack_array[edit->top_stack];
}

struct stack_num {
    double stack_array_int[MAX] = { 0.0 };
    int top_stack_num = -1;
    stack_num() { }
};

void pop_stack_num(stack_num* edit) {
    edit->top_stack_num--;
}

void push_stack_num(stack_num* edit, double to_push) {
    edit->top_stack_num++;
    edit->stack_array_int[edit->top_stack_num] = to_push;
}

bool is_empty_stack_num(stack_num* edit) {
    return edit->top_stack_num == -1;
}

void clear_stack_num(stack_num* edit) {
    memset(edit->stack_array_int, 0, sizeof(edit->stack_array_int));
}

double top_stack_num(stack_num* edit) {
    return edit->stack_array_int[edit->top_stack_num];
}


bool check_brackets(char operations[], stack* check) {
    for (int i = 0; operations[i] != '\0'; i++) {
        char bracket = operations[i];
        if (bracket == '(' || bracket == '{' || bracket == '[') {
            push_stack(check, bracket);
        }
        else if (bracket == ')' || bracket == '}' || bracket == ']') {
            if (is_empty_stack(check)) {
                return false;
            }
            char top_bracket = top_stack(check);
            if ((bracket == ')' && top_bracket != '(') ||
                (bracket == '}' && top_bracket != '{') ||
                (bracket == ']' && top_bracket != '[')) {
                clear_stack(check);
                return false;
            }
            pop_stack(check);

        }
    }
    return is_empty_stack(check);

}

int check_priority(char element) {
    if (element == '-' || element == '+') {
        return 1;
    }
    else if (element == '*' || element == '/') {
        return 2;
    }
    else {
        return 0;
    }
}

double calculate(double a, double b, char temp) {
    switch (temp) {
    case('+'):
        return b + a;
        break;
    case('-'):
        return b - a;
        break;
    case('*'):
        return b * a;
        break;
    case('/'):
        return b / a;
        break;
    }
}

double calculate_onp(queue* onp) {
    double result = 0;
    double temp_number = 0;
    char separator = ',';
    stack_num* calcualate_stack = new stack_num();
    for (int i = onp->front_queue + 1; i <= onp->tail_queue; i++) {
        char temp = onp->queue_array[i];
        if (temp >= 48 && temp <= 57) {
            temp_number = temp_number * 10 + (double(temp) - double('0'));
        }
        else if (temp == separator) {
            push_stack_num(calcualate_stack, temp_number);
            temp_number = 0;
        }
        else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
            double a = top_stack_num(calcualate_stack);
            pop_stack_num(calcualate_stack);
            double b = top_stack_num(calcualate_stack);
            pop_stack_num(calcualate_stack);
            result = calculate(a, b, temp);
            push_stack_num(calcualate_stack, result);
        }
    }
    result = top_stack_num(calcualate_stack);
    delete calcualate_stack;
    return result;
}

void convert_to_onp(char operations[]) {
    queue* out = new queue();
    stack* operators = new stack();
    int digits = -1;
    char separator = ',';
    for (int i = 0; operations[i] != '\0'; i++) {
        char element = operations[i];
        if (int(element) >= 48 && int(element) <= 57) {
            push_queue(out, element);
            digits++;
        }
        else if (element == '+' || element == '-' || element == '*' || element == '/') {
            if (digits > -1) {
                push_queue(out, separator);
                digits = -1;
            }
            if (!is_empty_stack(operators)) {
                char top_operator = top_stack(operators);
                while (check_priority(top_operator) >= check_priority(element) && !is_empty_stack(operators)) {
                    top_operator = top_stack(operators);
                    if (check_priority(top_operator)) {
                        push_queue(out, top_operator);
                    }
                    pop_stack(operators);
                }
                push_stack(operators, element);
            }
            else {
                push_stack(operators, element);
            }
        }
        else if (element == '(' || element == '{' || element == '[') {
            if (digits > -1) {
                push_queue(out, separator);
                digits = -1;
            }
            push_stack(operators, element);
        }
        else if ((element == ')' || element == '}' || element == ']')) {
            if (digits > -1) {
                push_queue(out, separator);
                digits = -1;
            }
            char top_operator = top_stack(operators);
            char to_find = '(';
            if (element == '}') {
                to_find = '{';
            }
            else if (element == ']') {
                to_find = '[';
            }
            while (!is_empty_stack(operators) && top_operator != to_find) {
                top_operator = top_stack(operators);
                if (top_operator != to_find) {
                    push_queue(out, top_operator);
                    pop_stack(operators);
                }
            }
            if (top_operator == to_find) {
                pop_stack(operators);
            }

        }
    }
    if (int(out->queue_array[out->tail_queue]) >= 48 && int(out->queue_array[out->tail_queue]) <= 57) {
        push_queue(out, separator);
    }
    while (!is_empty_stack(operators)) {
        char temp = top_stack(operators);
        push_queue(out, temp);
        if (!is_empty_stack(operators)) {
            pop_stack(operators);
        }
    }
    cout << calculate_onp(out) << "\n";
    delete out;
    delete operators;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n = 0;
    char operations[MAX];
    memset(operations, '\0', sizeof(operations));
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        cin.getline(operations, MAX);
        stack* check = new stack();
        if (check_brackets(operations, check)) {
            convert_to_onp(operations);
        }
        else {
            cout << "BLAD\n";
        }
        memset(operations, '\0', sizeof(operations));
    }
    return 0;
}
