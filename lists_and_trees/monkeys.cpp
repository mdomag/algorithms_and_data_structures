#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct monkey {
	char name;
	int children_count;
	vector<monkey*> children;
};

void preorder(monkey* root) {
	cout << root->name;
	for (monkey* child : root->children) {
		preorder(child);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int flag;
	int loop_count, monkey_count;
	cin >> loop_count;
	for (int i = 0; i < loop_count; i++) {
		cin >> monkey_count;
		if (monkey_count != 0) {
			queue <monkey*> monkeys;
			monkey* root = new monkey;
			for (int j = 0; j < monkey_count; j++) {
				if (j == 0) {
					cin >> root->name >> root->children_count;
					monkeys.push(root);
					flag = 1;
				}
				else {
					monkey* child = new monkey;
					cin >> child->name >> child->children_count; 
					if (monkeys.front()->children_count != 0) { //sprawdza czy malpka moze przyjac dzieci
						if (flag < monkeys.front()->children_count) {
							monkeys.front()->children.push_back(child);
							monkeys.push(child);
							flag++;
						}
						else if (flag == monkeys.front()->children_count) {
							monkeys.front()->children.push_back(child);
							monkeys.pop(); //zdejmuje obecny front
							monkeys.push(child);
							flag = 1;
						}
					}
				}
			}
			if (root != nullptr) {
				preorder(root);
				cout << "\n";
			}
			delete root;
		}
	}
	return 0;
}
