#include "Tree.h"
void do_assert(const std::string& expression) {
	std::cout << expression << std::endl;
	assert(0);
}
int read_int(const char* string, int& num)
{
	int current_num = 0;
	bool sign = true;

	if (*string == '-') {
		sign = false;
		current_num++;
	}

	if (!('0' <= string[current_num] && string[current_num] <= '9'))
		return -1;

	num = 0;
	while ('0' <= string[current_num] && string[current_num] <= '9') {
		num = num * 10 + (string[current_num] - '0');
		current_num++;
	}

	if (!sign)
		num *= -1;
	return current_num;
}
int read_double(const char* string, double& num)
{
	int current_num = 0;
	bool sign = true;

	if (*string == '-') {
		sign = false;
		current_num++;
	}

	if (!('0' <= string[current_num] && string[current_num] <= '9'))
		return -1;

	int result = 0;
	while ('0' <= string[current_num] && string[current_num] <= '9') {
		result = result * 10 + (string[current_num] - '0');
		current_num++;
	}
	if (string[current_num] == '.') {
		int result_fraq = 0;
		current_num++;
		int fraq_num = 0;

		while ('0' <= string[current_num] && string[current_num] <= '9') {
			result_fraq = result_fraq * 10 + (string[current_num] - '0');
			current_num++;
			fraq_num++;
		}

		num = double(result_fraq);
		for (int i = 0; i < fraq_num; ++i)
			num /= 10;

		num += double(result);
	}
	else
		num = double(result);


	if (!sign)
		num *= -1;
	return current_num;
}


int skip_brackets(const char* string)
{
	int shift = 0;
	while (*string == ')') {
		string++;
		shift++;
	}
	return shift;
}


double read_dif_var(const char* string, int* shift)
{
	double answer = -1;

	assert(string[0] == 'x');

	switch (string[1]) {
	case '1':
		answer = VALUE_X1;
		*shift = 3;
		break;
	case '2':
		answer = VALUE_X2;
		*shift = 3;
		break;
	case '3':
		answer = VALUE_X3;
		*shift = 3;
		break;
	case '4':
		answer = VALUE_X4;
		*shift = 3;
		break;
	default:
		printf("No such variable for differencing!\n");
		assert(0);
		break;
	}
	
	assert(string[2] == ':');

	return answer;
}

//Warning! Both change the current_symbol in string --------------
double read_operation(const char*& string)
{
	switch (*string) {
	case '+':
		string++;
		return OP_ADD;
	case '-':
		string++;
		return OP_SUB;
	case '*':
		string++;
		return OP_MULT;
	case '/':
		string++;
		return OP_DIV;
	case '^':
		string++;
		return OP_DEG;
	case 's':
		if (string[1] == 'i' && string[2] == 'n') {
			string += 3;
			return OP_SIN;
		}
		else
			do_assert("Such operation not found!\n");
	case 'c':
		if (string[1] == 'o' && string[2] == 's') {
			string += 3;
			return OP_COS;
		}
		else
			do_assert("Such operation not found!\n");
	}
	return OP_EMPTY;
}
double read_var(const char*& string) {
	assert(*string == 'x');
	switch (string[1])
	{
	case '1':
		string += 2;
		return VALUE_X1;
	case '2':
		string += 2;
		return VALUE_X2;
	case '3':
		string += 2;
		return VALUE_X3;
	case '4':
		string += 2;
		return VALUE_X4;
	}
	printf("Variable number wasn't found!\n");
	assert(0);
	return 0;
}
//------------------------------------------------------------------


double do_operation(const double number_operation, double x = 0, double y = 0) {

	if (number_operation == OP_EMPTY) {
		do_assert("EMPTY OPERATION!\n");
	}

	if (number_operation == OP_ADD) {
		return (x + y);
	}
	if (number_operation == OP_SUB) {
		return (x - y);
	}
	if (number_operation == OP_MULT) {
		return (x * y);
	}
	if (number_operation == OP_DIV) {
		if (y == 0)
			do_assert("Dividing by zero!\n");
		return (x / y);
	}
	if (number_operation == OP_DEG) {
		if (x == 0 && y == 0) {
			do_assert(std::string("Zero in zero degree!\n"));
		}

		double answer = x;
		for (int i = 1; i < y; ++i)
			answer *= x;
		return answer;
	}  
	if (number_operation == OP_SIN) {
		if (fabs(x) >= 5)
			return 0;
		return (x - x * x * x / 6 + x * x * x * x * x / 120);
	}
	if (number_operation == OP_COS) {
		if (fabs(x) >= 5.0)
			return 0;
		return (1 - x * x / 2 + x * x * x * x / 24);
	}

	do_assert(std::string("Forbidden operation!\n"));
	return -1;
}
double safechecking_do_operation(const double number_operation, bool& safe, double x = 0, double y = 0) {

	if (number_operation == OP_EMPTY) {
		printf("\nEMPTY OPERATION!\n");
		safe = false;
		return 0;
	}

	if (number_operation == OP_ADD) {
		return (x + y);
	}
	if (number_operation == OP_SUB) {
		return (x - y);
	}
	if (number_operation == OP_MULT) {
		return (x * y);
	}
	if (number_operation == OP_DIV) {
		if (y == 0) {
			safe = false;
			printf("\nDIVIDING BY ZERO!\n");
			return 0;
		}
		return (x / y);
	}
	if (number_operation == OP_DEG) {
		if (x == 0 && y == 0) {
			safe = false;
			printf("\nZERO IN ZERO DEGREE!\n");
		}

		double answer = x;
		for (int i = 1; i < y; ++i)
			answer *= x;
		return answer;
	}
	if (number_operation == OP_SIN) {
		if (fabs(x) >= 5)
			return 0;
		return (x - x * x * x / 6 + x * x * x * x * x / 120);
	}
	if (number_operation == OP_COS) {
		if (fabs(x) >= 5.0)
			return 0;
		return (1 - x * x / 2 + x * x * x * x / 24);
	}

	safe = false;
	printf("\nFORBIDDEN OPERATION!\n");
	return -1;
}

double make_avarage(double num, int aproximate)
{
	for (int i = 0; i < aproximate; ++i) {
		num *= 10;
	}
	double answer = round(num);

	for (int i = 0; i < aproximate; ++i) {
		answer /= 10;
	}
	return answer;
}






Node::Node():
	type_(Type::Empty),
	value_(-1),
	
	parent_(nullptr),
	left_(nullptr),
	right_(nullptr)
{}
Node::Node(Node* new_parent) : Node()
{ 
	parent_ = new_parent;
}
Node::Node(Type new_type, double new_value) :
	type_(new_type),
	value_(new_value),

	parent_(nullptr),
	left_(nullptr),
	right_(nullptr)
{}
Node::Node(Type new_type, double new_value, Node* new_parent): Node(new_type, new_value)
{
	parent_ = new_parent;
}

void Node::fill_Node(Type new_type, double new_value)
{
	type_ = new_type;
	value_ = new_value;
}
void Node::fill_Node(Type new_type, double new_value, Node* new_parent)
{
	type_ = new_type;
	value_ = new_value;
	parent_ = new_parent;
}

void Node::copy_data(const Node* other_Node)
{
	this->type_ = other_Node->get_type();
	this->value_ = other_Node->get_value();
}





Tree::Tree() :
	main_Node_(new Node),
	size_(1),
	dif_var_((double)-1),
	SavingTrees()
{}
Tree::~Tree()
{
	destroy(main_Node_);
}

void Tree::read_string_to_Tree(const char* current_symbol)
{
	int shift = 0;
	dif_var_ = read_dif_var(current_symbol, &shift);
	current_symbol += shift;
	
	read_string_to_Tree(main_Node_, current_symbol);
	
	simplify_tree(main_Node_);
	simplify_tree(main_Node_);
	return;
}
Node* Tree::read_string_to_Tree(Node* current_Node, const char*& current_symbol)
{
	while (*current_symbol == ')')
		current_symbol++;
	if (*current_symbol == '\0')
		return current_Node;

	
	if (*current_symbol == '(') {
		Node* new_left_Node = new Node(current_Node);

		size_++;
		current_symbol++;
		current_Node->left_ = read_string_to_Tree(new_left_Node, current_symbol);
	}
	while (*current_symbol == ')')
		current_symbol++;

	if (*current_symbol == 'x') {
		current_Node->fill_Node(Type::Var, read_var(current_symbol));
		return current_Node;
	}

	if (('0' <= *current_symbol && *current_symbol <= '9') || (*(current_symbol - 1) == '(' && *current_symbol == '-')) {
		double new_num = 0;
		int shift = read_double(current_symbol, new_num);

		current_Node->fill_Node(Type::Num, new_num);
		current_symbol += shift;
		return current_Node;
	}

	double current_operation = read_operation(current_symbol);
	if (current_operation != OP_EMPTY){

		current_Node->fill_Node(Type::Op, current_operation);

		if (current_operation == OP_SIN || current_operation == OP_COS) {
			Node* new_left_Node = new Node(current_Node);
			Node* new_right_Node = new Node(Type::Num, 0, current_Node);
			size_ += 2;
			current_Node->left_ = read_string_to_Tree(new_left_Node, current_symbol);
			current_Node->right_ = new_right_Node;
		}
		else {
			Node* new_right_Node = new Node(current_Node);
			size_++;
			current_Node->right_ = read_string_to_Tree(new_right_Node, current_symbol);
		}
	}
	
	return current_Node;
}
bool Tree::is_safe(double* variables) const
{
	bool safe = true;
	for (std::size_t i = 0; i < SavingTrees.size(); ++i) {
		//printf("\n");
		//SavingTrees[i]->print();
		//printf("\n");
		SavingTrees[i]->safechecking_get_answer(SavingTrees[i]->main_Node_, safe, variables);
	}
	return safe;
}


void Tree::print() const
{
	printf("\\[");
	this->print(main_Node_);
	printf("\\]");
}
void Tree::print(Node* current_Node) const
{
	if (current_Node->left_ == nullptr && current_Node->right_ == nullptr) {
		if (current_Node->is_full())
			print_element(current_Node);
		return;
	}
	
	Type current_type = current_Node->get_type();
	double current_value = current_Node->get_value();

	if (current_type != Type::Op)
		print_element(current_Node);

	if (current_type == Type::Op && (current_value == OP_SIN || current_value == OP_COS)) {
		print_element(current_Node);
		printf("{");
		print(current_Node->left_);
		printf("}");
		return;
	}
	if (current_type == Type::Op && (current_value == OP_DIV)) {
		print_element(current_Node);
		printf("{");
		print(current_Node->left_);
		printf("}{");
		print(current_Node->right_);
		printf("}");
		return;
	}
	if (current_type == Type::Op && (current_value == OP_DEG)) {
		print(current_Node->left_);
		printf("^{");
		print(current_Node->right_);
		printf("}");
		return;
	}

	if (current_Node->left_ != nullptr) {
		if (current_Node->left_->get_type() != Type::Op || (current_Node->left_->get_type() == Type::Op && (current_Node->left_->get_value() == OP_SIN || current_Node->left_->get_value() == OP_COS || current_Node->left_->get_value() == OP_DEG)))
			print(current_Node->left_);
		else {
			printf("(");
			print(current_Node->left_);
			printf(")");
		}
	}

	print_element(current_Node);

	if (current_Node->right_ != nullptr) {
		if (current_Node->right_->get_type() != Type::Op || (current_Node->right_->get_type() == Type::Op && (current_Node->right_->get_value() == OP_SIN || current_Node->right_->get_value() == OP_COS || current_Node->right_->get_value() == OP_DEG)))
			print(current_Node->right_);
		else {
			printf("(");
			print(current_Node->right_);
			printf(")");
		}
	}
}
void Tree::print_element(Node* current_Node) const
{
	Type current_type = current_Node->get_type();
	double current_value = current_Node->get_value();

	if (current_type == Type::Num) {
		printf("%.2lf", make_avarage(current_value, 2));
		return;
	}
	if (current_type == Type::Var) {
		if (current_value == VALUE_X1) {
			printf("x1");
			return;
		}
		if (current_value == VALUE_X2) {
			printf("x2");
			return;
		}
		if (current_value == VALUE_X3) {
			printf("x3");
			return;
		}
		if (current_value == VALUE_X4) {
			printf("x4");
			return;
		}
		printf("No such varuable!\n");
		assert(0);
	}
	if (current_type == Type::Op) {
		if (current_value == OP_ADD) {
			printf("+");
			return;
		}
		if (current_value == OP_SUB) {
			printf("-");
			return;
		}
		if (current_value == OP_MULT) {
			printf("*");
			return;
		}
		if (current_value == OP_DIV) {
			printf("\\frac");
			return;
		}
		if (current_value == OP_DEG) {
			printf("^");
			return;
		}
		if (current_value == OP_SIN) {
			printf("\\sin");
			return;
		}
		if (current_value == OP_COS) {
			printf("\\cos");
			return;
		}
		do_assert("No such operation !\n");
	}

	do_assert("Problems with printing element!\n");
}



Node* Tree::dif(Node* current_Node, const Node* original_Node)
{
	Type current_type = original_Node->get_type();
	if (current_type == Type::Num) {
		current_Node->fill_Node(Type::Num, 0);
		return current_Node;
	}
	if (current_type == Type::Var) {
		if (fabs(original_Node->get_value() - dif_var_) < APROX) {
			current_Node->fill_Node(Type::Num, 1);
			return current_Node;
		}
		else {
			current_Node->fill_Node(Type::Num, 0);
			return current_Node;
		}
	}
	
	double current_value = original_Node->get_value();

	if (current_value == OP_ADD || current_value == OP_SUB) {
		current_Node->copy_data(original_Node);

		Node* left_Node = new Node(current_Node);
		Node* right_Node = new Node(current_Node);

		current_Node->left_ = dif(left_Node, original_Node->left_);
		current_Node->right_ = dif(right_Node, original_Node->right_);
		return current_Node;
	}
	if (current_value == OP_MULT) {
		current_Node->fill_Node(Type::Op, OP_ADD);

		Node* left_Node = new Node(Type::Op, OP_MULT, current_Node);
		Node* right_Node = new Node(Type::Op, OP_MULT, current_Node);
		current_Node->left_ = left_Node;
		current_Node->right_ = right_Node;


		Node* left_left_Node = new Node(left_Node);
		Node* right_left_Node = new Node(right_Node);
		left_Node->left_ = dif(left_left_Node, original_Node->left_);
		right_Node->left_ = dif(right_left_Node, original_Node->right_);


		Node* left_right_Node = new Node(left_Node);
		Node* right_right_Node = new Node(right_Node);
		left_Node->right_ = copy_tree(left_right_Node, original_Node->right_);
		right_Node->right_ = copy_tree(right_right_Node, original_Node->left_);

		return current_Node;
	}
	if (current_value == OP_DIV) {
		current_Node->fill_Node(Type::Op, OP_DIV);

		Node* right_Node = new Node(Type::Op, OP_MULT, current_Node);
		Node* left_Node = new Node(Type::Op, OP_SUB, current_Node);
		current_Node->right_ = right_Node;
		current_Node->left_ = left_Node;


		Node* right_left_Node = new Node(right_Node);
		Node* right_right_Node = new Node(right_Node);
		right_Node->left_ = copy_tree(right_left_Node, original_Node->right_);
		right_Node->right_ = copy_tree(right_right_Node, original_Node->right_);



		
		Node* left_left_Node = new Node(Type::Op, OP_MULT, left_Node);
		Node* left_right_Node = new Node(Type::Op, OP_MULT, left_Node);
		left_Node->left_ = left_left_Node;
		left_Node->right_ = left_right_Node;


		Node* left_left_left_Node = new Node(left_left_Node);
		Node* left_right_left_Node = new Node(left_right_Node);
		left_left_Node->left_ = dif(left_left_left_Node, original_Node->left_);
		left_right_Node->left_ = dif(left_right_left_Node, original_Node->right_);


		Node* left_left_right_Node = new Node(left_left_Node);
		Node* left_right_right_Node = new Node(left_right_Node);
		left_left_Node->right_ = copy_tree(left_left_right_Node, original_Node->right_);
		left_right_Node->right_ = copy_tree(left_right_right_Node, original_Node->left_);

		return current_Node;
	}
	if (current_value == OP_DEG && original_Node->right_->get_type() == Type::Num) {
		
		current_Node->fill_Node(Type::Op, OP_MULT);
		Node* left_Node = new Node(Type::Num, original_Node->right_->get_value(), current_Node);
		current_Node->left_ = left_Node;

		Node* right_Node = new Node(Type::Op, OP_MULT, current_Node);
		current_Node->right_ = right_Node;

		Node* right_right_Node = new Node(right_Node);
		right_Node->right_ = dif(right_right_Node, original_Node->left_);

		Node* right_left_Node = new Node(Type::Op, OP_DEG, right_Node);
		right_Node->left_ = right_left_Node;

		Node* right_left_left_Node = new Node(right_left_Node);
		right_left_Node->left_ = copy_tree(right_left_left_Node, original_Node->left_);

		Node* right_left_right_Node = new Node(Type::Num, original_Node->right_->get_value() - 1, right_left_Node);
		right_left_Node->right_ = right_left_right_Node;

		return current_Node;
	}
	if (current_value == OP_SIN) {
		current_Node->fill_Node(Type::Op, OP_MULT);

		Node* right_Node = new Node(Type::Op, OP_COS, current_Node);
		Node* left_Node = new Node(current_Node);

		current_Node->right_ = right_Node;
		current_Node->left_ = dif(left_Node, original_Node->left_);

		Node* right_left_Node = new Node(right_Node);
		Node* right_right_Node = new Node(Type::Num, 0, right_Node);
		right_Node->left_ = copy_tree(right_left_Node, original_Node->left_);
		right_Node->right_ = right_right_Node;

		return current_Node;
	}
	if (current_value == OP_COS) {
		current_Node->fill_Node(Type::Op, OP_MULT);

		Node* right_Node = new Node(Type::Op, OP_MULT, current_Node);
		Node* left_Node = new Node(current_Node);

		current_Node->right_ = right_Node;
		current_Node->left_ = dif(left_Node, original_Node->left_);

		Node* right_left_Node = new Node(Type::Num, -1, left_Node);
		Node* right_right_Node = new Node(Type::Op, OP_SIN, left_Node);
		right_Node->left_ = right_left_Node;
		right_Node->right_ = right_right_Node;

		Node* right_right_left_Node = new Node(right_right_Node);
		Node* right_right_right_Node = new Node(Type::Num, 0, right_right_Node);
		right_right_Node->left_ = copy_tree(right_right_left_Node, original_Node->left_);
		right_right_Node->right_ = right_right_right_Node;

		return current_Node;
	}

	do_assert("Mistake with differencial operation!\n");
	return current_Node;
}
void Tree::dif(const Tree& original)
{
	dif_var_ = original.get_dif_var();
	dif(main_Node_, original.get_main_Node());
	
	simplify_tree(main_Node_);
	simplify_tree(main_Node_);
	return;
}

double Tree::operator() (double* variables) const
{
	if (!(is_safe(variables))) {
		printf("Are you sure to comlete your unsafe operation? [y/n]\n");
		
		char sign = '0';
		while (!(scanf_s("%c", &sign, sizeof(sign)) == 1 && (sign == 'y' || sign == 'n')));
		if (sign == 'n') {
			printf("Operation was stopped\n");
			return -1;
		}
	}
	return get_answer(main_Node_, variables);
}
double Tree::get_answer(const Node* current_Node, const double* variables) const
{
	Type current_type = current_Node->get_type();

	if (current_type == Type::Num)
		return current_Node->get_value();
	if (current_type == Type::Var)
		return variables[(int)current_Node->get_value()];
	if (current_Node->left_ != nullptr && current_Node->right_ != nullptr && current_type == Type::Op)
		return do_operation(current_Node->get_value(), get_answer(current_Node->left_, variables), get_answer(current_Node->right_, variables));

	do_assert("Can't find the result of expression!\n");
	return -1;
}
double Tree::safechecking_get_answer(const Node* current_Node, bool& safe, double* variables) const
{
	Type current_type = current_Node->get_type();

	if (current_type == Type::Num)
		return current_Node->get_value();
	if (current_type == Type::Var)
		return variables[(int)current_Node->get_value()];
	if (current_Node->left_ != nullptr && current_Node->right_ != nullptr && current_type == Type::Op)
		return safechecking_do_operation(current_Node->get_value(), safe, get_answer(current_Node->left_, variables), get_answer(current_Node->right_, variables));

	do_assert("Can't find the result of expression!\n");
	return -1;
}


void Tree::simplify_tree(Node* current_Node)
{
	if (current_Node->get_type() == Type::Num || current_Node->get_type() == Type::Var)
		return;

	if (current_Node->left_->get_type() == Type::Op)
		simplify_tree(current_Node->left_);
	if (current_Node->right_->get_type() == Type::Op)
		simplify_tree(current_Node->right_);

	Type left_type = current_Node->left_->get_type();
	double left_value = current_Node->left_->get_value();

	Type right_type = current_Node->right_->get_type();
	double right_value = current_Node->right_->get_value();

	Type current_type = current_Node->get_type();
	double current_value = current_Node->get_value();

	if (compare_trees(current_Node->left_, current_Node->right_)) {
		if (current_value == OP_MULT) {
			current_Node->fill_Node(Type::Op, OP_DEG);
			
			destroy(current_Node->right_);
			Node* right_Node = new Node(Type::Num, 2, current_Node);
			current_Node->right_ = right_Node;
		}
		if (current_value == OP_ADD) {
			current_Node->fill_Node(Type::Op, OP_MULT);

			destroy(current_Node->left_);
			Node* left_Node = new Node(Type::Num, 2, current_Node);
			current_Node->left_ = left_Node;
		}
		if (current_value == OP_SUB) {
			current_Node->fill_Node(Type::Num, 0);
			create_saving_tree(current_Node->right_);
			destroy_under_Node(current_Node);
		}
		if (current_value == OP_DIV) {
			create_saving_tree(current_Node->right_);
			current_Node->fill_Node(Type::Num, 1);
			destroy_under_Node(current_Node);
		}
		return;
	}

	if (left_type == Type::Num && right_type == Type::Num) {
		current_Node->fill_Node(Type::Num, do_operation(current_value, left_value, right_value));
		destroy_under_Node(current_Node);
		return;
	}
	if (left_type == Type::Num) {

		if (left_value == 0) {
			if (current_value == OP_ADD) {
				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->right_;
					destroy(current_Node->left_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->left_);
					current_Node->right_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->right_;
					else
						current_Node->parent_->right_ = current_Node->right_;

					destroy_one_Node(current_Node);
				}
			}
			if (current_value == OP_MULT) {
				create_saving_tree(current_Node->right_);
				current_Node->fill_Node(Type::Num, 0);
				destroy_under_Node(current_Node);
			}
			if (current_value == OP_DIV) {
				create_saving_tree(current_Node);
				current_Node->fill_Node(Type::Num, 0);
				destroy_under_Node(current_Node);
			}
			if (current_value == OP_SUB) {
				current_Node->fill_Node(Type::Op, OP_MULT);
				current_Node->left_->fill_Node(Type::Num, -1);
			}
			return;
		}
		if (left_value == 1 && current_value == OP_MULT) {
			if (current_Node->parent_ == nullptr) {
				main_Node_ = current_Node->right_;
				destroy(current_Node->left_);
				destroy_one_Node(current_Node);
				main_Node_->parent_ = nullptr;
			}
			else {
				destroy(current_Node->left_);
				current_Node->right_->parent_ = current_Node->parent_;
				if (current_Node->parent_->left_ == current_Node)
					current_Node->parent_->left_ = current_Node->right_;
				else
					current_Node->parent_->right_ = current_Node->right_;

				destroy_one_Node(current_Node);
			}
			return;
		}
	}
	if (right_type == Type::Num) {

		if (right_value == 0) {
			if (current_value == OP_ADD || current_value == OP_SUB) {
				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->left_;
					destroy(current_Node->right_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->right_);
					current_Node->left_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->left_;
					else
						current_Node->parent_->right_ = current_Node->left_;

					destroy_one_Node(current_Node);
				}
			}
			if (current_value == OP_MULT) {
				create_saving_tree(current_Node->left_);
				current_Node->fill_Node(Type::Num, 0);
				destroy_under_Node(current_Node);
			}
			if (current_value == OP_DEG) {
				create_saving_tree(current_Node);
				current_Node->fill_Node(Type::Num, 1);
				destroy_under_Node(current_Node);
			}
			if (current_value == OP_DIV) {
				do_assert("Dividing by zero!\n");
			}
			return;
		}
		if (right_value == 1 && (current_value == OP_MULT || current_value == OP_DEG || current_value == OP_DIV)) {
			if (current_Node->parent_ == nullptr) {
				main_Node_ = current_Node->left_;
				destroy(current_Node->right_);
				destroy_one_Node(current_Node);
				main_Node_->parent_ = nullptr;
			}
			else {
				destroy(current_Node->right_);
				current_Node->left_->parent_ = current_Node->parent_;
				if (current_Node->parent_->left_ == current_Node)
					current_Node->parent_->left_ = current_Node->left_;
				else
					current_Node->parent_->right_ = current_Node->left_;
				
				destroy_one_Node(current_Node);
			}
			return;
		}

	}
	

	if (current_type == Type::Op && left_type == Type::Num && right_type == Type::Op) {

		Type right_left_type = current_Node->right_->left_->get_type();
		Type right_right_type = current_Node->right_->right_->get_type();

		if (right_left_type == Type::Num) {
			if (current_value == OP_ADD && (right_value == OP_ADD || right_value == OP_SUB)) {

				current_Node->right_->left_->fill_Node(Type::Num, do_operation(OP_ADD, left_value, current_Node->right_->left_->get_value()));
				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->right_;
					destroy(current_Node->left_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->left_);
					current_Node->right_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->right_;
					else
						current_Node->parent_->right_ = current_Node->right_;

					destroy_one_Node(current_Node);
				}
				return;
			}
			if (current_value == OP_SUB && (right_value == OP_ADD || right_value == OP_SUB)) {

				current_Node->right_->left_->fill_Node(Type::Num, do_operation(OP_SUB, left_value, current_Node->right_->left_->get_value()));
				if (right_value == OP_ADD)
					current_Node->right_->fill_Node(Type::Op, OP_SUB);
				else
					current_Node->right_->fill_Node(Type::Op, OP_ADD);

				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->right_;
					destroy(current_Node->left_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->left_);
					current_Node->right_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->right_;
					else
						current_Node->parent_->right_ = current_Node->right_;

					destroy_one_Node(current_Node);
				}
				return;
			}
			if (current_value == OP_MULT && ((right_value == OP_MULT || right_value == OP_DIV))) {

				current_Node->right_->left_->fill_Node(Type::Num, do_operation(OP_MULT, left_value, current_Node->right_->left_->get_value()));
				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->right_;
					destroy(current_Node->left_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->left_);
					current_Node->right_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->right_;
					else
						current_Node->parent_->right_ = current_Node->right_;

					destroy_one_Node(current_Node);
				}
				return;
			}
			if (current_value == OP_DIV && ((right_value == OP_MULT || right_value == OP_DIV))) {

				current_Node->right_->left_->fill_Node(Type::Num, do_operation(OP_DIV, left_value, current_Node->right_->left_->get_value()));
				if (right_value == OP_MULT)
					current_Node->right_->fill_Node(Type::Op, OP_DIV);
				else
					current_Node->right_->fill_Node(Type::Op, OP_MULT);

				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->right_;
					destroy(current_Node->left_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->left_);
					current_Node->right_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->right_;
					else
						current_Node->parent_->right_ = current_Node->right_;

					destroy_one_Node(current_Node);
				}
				return;
			}
			if (current_value == OP_DEG && right_value == OP_MULT) {
				current_Node->left_->fill_Node(Type::Num, do_operation(OP_DEG, left_value, current_Node->right_->left_->get_value()));
				current_Node->right_ = current_Node->right_->right_;

				destroy_one_Node(current_Node->right_->parent_->left_);
				destroy_one_Node(current_Node->right_->parent_);

				current_Node->right_->parent_ = current_Node;
			}
		}
		if (right_right_type == Type::Num) {
			if (current_value == OP_ADD && (right_value == OP_ADD || right_value == OP_SUB)) {

				if (right_value == OP_ADD)
					current_Node->right_->right_->fill_Node(Type::Num, do_operation(OP_ADD, left_value, current_Node->right_->right_->get_value()));
				else
					current_Node->right_->right_->fill_Node(Type::Num, do_operation(OP_SUB, current_Node->right_->right_->get_value(), left_value));

				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->right_;
					destroy(current_Node->left_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->left_);
					current_Node->right_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->right_;
					else
						current_Node->parent_->right_ = current_Node->right_;

					destroy_one_Node(current_Node);
				}
				return;
			}
			if (current_value == OP_SUB && (right_value == OP_ADD || right_value == OP_SUB)) {

				if (right_value == OP_ADD)
					current_Node->left_->fill_Node(Type::Num, do_operation(OP_SUB, left_value, current_Node->right_->right_->get_value()));
				else
					current_Node->left_->fill_Node(Type::Num, do_operation(OP_ADD, left_value, current_Node->right_->right_->get_value()));

				destroy(current_Node->right_->right_);
				current_Node->right_ = current_Node->right_->left_;
				destroy_one_Node(current_Node->right_->parent_);
				return;
			}
			if (current_value == OP_MULT && ((right_value == OP_MULT || right_value == OP_DIV))) {

				if (right_value == OP_MULT)
					current_Node->right_->right_->fill_Node(Type::Num, do_operation(OP_MULT, left_value, current_Node->right_->right_->get_value()));
				else {
					if (left_value > current_Node->right_->right_->get_value()) {
						current_Node->right_->right_->fill_Node(Type::Num, do_operation(OP_DIV, left_value, current_Node->right_->right_->get_value()));
						current_Node->right_->fill_Node(Type::Op, OP_MULT);
					}
					else
						current_Node->right_->right_->fill_Node(Type::Num, do_operation(OP_DIV, current_Node->right_->right_->get_value(), left_value));
				}

				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->right_;
					destroy(current_Node->left_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->left_);
					current_Node->right_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->right_;
					else
						current_Node->parent_->right_ = current_Node->right_;

					destroy_one_Node(current_Node);
				}
				return;
			}
			if (current_value == OP_DIV && ((right_value == OP_MULT || right_value == OP_DIV))) {

				if (right_value == OP_MULT)
					current_Node->left_->fill_Node(Type::Num, do_operation(OP_DIV, left_value, current_Node->right_->right_->get_value()));
				else
					current_Node->left_->fill_Node(Type::Num, do_operation(OP_MULT, left_value, current_Node->right_->right_->get_value()));

				
				destroy(current_Node->right_->right_);
				current_Node->right_ = current_Node->right_->left_;
				destroy_one_Node(current_Node->right_->parent_);
				return;
			}
			if (current_value == OP_DEG && right_value == OP_MULT) {
				current_Node->left_->fill_Node(Type::Num, do_operation(OP_DEG, left_value, current_Node->right_->right_->get_value()));
				current_Node->right_ = current_Node->right_->left_;

				destroy_one_Node(current_Node->right_->parent_->right_);
				destroy_one_Node(current_Node->right_->parent_);

				current_Node->right_->parent_ = current_Node;
			}
		}
	}
	if (current_type == Type::Op && right_type == Type::Num && left_type == Type::Op) {

		Type left_left_type = current_Node->left_->left_->get_type();
		Type left_right_type = current_Node->left_->right_->get_type();

		if (left_left_type == Type::Num) {
			if (current_value == OP_ADD && (left_value == OP_ADD || left_value == OP_SUB)) {

				current_Node->left_->left_->fill_Node(Type::Num, do_operation(OP_ADD, right_value, current_Node->left_->left_->get_value()));
				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->left_;
					destroy(current_Node->right_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->right_);
					current_Node->left_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->left_;
					else
						current_Node->parent_->right_ = current_Node->left_;

					destroy_one_Node(current_Node);
				}
				return;
			}
			if (current_value == OP_SUB && (left_value == OP_ADD || left_value == OP_SUB)) {

				current_Node->left_->left_->fill_Node(Type::Num, do_operation(OP_SUB, current_Node->left_->left_->get_value(), right_value));
				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->left_;
					destroy(current_Node->right_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->right_);
					current_Node->left_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->left_;
					else
						current_Node->parent_->right_ = current_Node->left_;

					destroy_one_Node(current_Node);
				}
				return;
			}
			if (current_value == OP_MULT && (left_value == OP_MULT || left_value == OP_DIV)) {

				current_Node->left_->left_->fill_Node(Type::Num, do_operation(OP_MULT, current_Node->left_->left_->get_value(), right_value));
				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->left_;
					destroy(current_Node->right_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->right_);
					current_Node->left_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->left_;
					else
						current_Node->parent_->right_ = current_Node->left_;

					destroy_one_Node(current_Node);
				}
				return;
			}
			if (current_value == OP_DIV && (left_value == OP_MULT || left_value == OP_DIV)) {

				current_Node->left_->left_->fill_Node(Type::Num, do_operation(OP_DIV, current_Node->left_->left_->get_value(), right_value));
				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->left_;
					destroy(current_Node->right_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->right_);
					current_Node->left_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->left_;
					else
						current_Node->parent_->right_ = current_Node->left_;

					destroy_one_Node(current_Node);
				}
				return;
			}
		}
		if (left_right_type == Type::Num) {
			if (current_value == OP_ADD && (left_value == OP_ADD || left_value == OP_SUB)) {

				current_Node->left_->right_->fill_Node(Type::Num, do_operation(OP_ADD, right_value, current_Node->left_->right_->get_value()));
				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->left_;
					destroy(current_Node->right_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->right_);
					current_Node->left_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->left_;
					else
						current_Node->parent_->right_ = current_Node->left_;

					destroy_one_Node(current_Node);
				}
				return;
			}
			if (current_value == OP_SUB && (left_value == OP_ADD || left_value == OP_SUB)) {

				current_Node->left_->right_->fill_Node(Type::Num, do_operation(OP_SUB, current_Node->left_->right_->get_value(), right_value));
				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->left_;
					destroy(current_Node->right_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->right_);
					current_Node->left_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->left_;
					else
						current_Node->parent_->right_ = current_Node->left_;

					destroy_one_Node(current_Node);
				}
				return;
			}
			if (current_value == OP_MULT && (left_value == OP_MULT || left_value == OP_DIV)) {

				if (left_value == OP_MULT)
					current_Node->left_->right_->fill_Node(Type::Num, do_operation(OP_MULT, current_Node->left_->right_->get_value(), right_value));
				else
					current_Node->left_->right_->fill_Node(Type::Num, do_operation(OP_DIV, current_Node->left_->right_->get_value(), right_value));

				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->left_;
					destroy(current_Node->right_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->right_);
					current_Node->left_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->left_;
					else
						current_Node->parent_->right_ = current_Node->left_;

					destroy_one_Node(current_Node);
				}
				return;
			}
			if (current_value == OP_DIV && (left_value == OP_MULT || left_value == OP_DIV)) {

				if (left_value == OP_MULT)
					current_Node->left_->right_->fill_Node(Type::Num, do_operation(OP_DIV, current_Node->left_->right_->get_value(), right_value));
				else 
					current_Node->left_->right_->fill_Node(Type::Num, do_operation(OP_MULT, current_Node->left_->right_->get_value(), right_value));

				if (current_Node->parent_ == nullptr) {
					main_Node_ = current_Node->left_;
					destroy(current_Node->right_);
					destroy_one_Node(current_Node);
					main_Node_->parent_ = nullptr;
				}
				else {
					destroy(current_Node->right_);
					current_Node->left_->parent_ = current_Node->parent_;
					if (current_Node->parent_->left_ == current_Node)
						current_Node->parent_->left_ = current_Node->left_;
					else
						current_Node->parent_->right_ = current_Node->left_;

					destroy_one_Node(current_Node);
				}
				return;
			}
			if (current_value == OP_DEG && left_value == OP_DEG) {
				current_Node->right_->fill_Node(Type::Num, do_operation(OP_MULT, right_value, current_Node->left_->right_->get_value()));
				current_Node->left_ = current_Node->left_->left_;

				destroy_one_Node(current_Node->left_->parent_->right_);
				destroy_one_Node(current_Node->left_->parent_);

				current_Node->left_->parent_ = current_Node;
			}
		}
		return;
	}

	return;
}
void Tree::create_saving_tree(Node* dangerous_main_Node)
{
	if (dangerous_main_Node == nullptr)
		return;

	Tree* new_dangerous_tree = new Tree;
	copy_tree(new_dangerous_tree->main_Node_, dangerous_main_Node);
	SavingTrees.push_back(new_dangerous_tree);
}



Node* Tree::copy_tree(Node* current_Node, const Node* original_Node)
{
	current_Node->copy_data(original_Node);

	if (original_Node->left_ != nullptr) {
		Node* left_Node = new Node(current_Node);
		current_Node->left_ = copy_tree(left_Node, original_Node->left_);
	}
	if (original_Node->right_ != nullptr) {
		Node* right_Node = new Node(current_Node);
		current_Node->right_ = copy_tree(right_Node, original_Node->right_);
	}
	return current_Node;
}
bool Tree::compare_trees(Node* first_tree, Node* second_tree)
{
	if (first_tree == nullptr && second_tree == nullptr)
		return true;
	if (first_tree == nullptr || second_tree == nullptr)
		return false;

	if (!compare_trees(first_tree->left_, second_tree->left_))
		return false;
	if (!compare_trees(first_tree->right_, second_tree->right_))
		return false;

	if (first_tree->get_type() == second_tree->get_type() && first_tree->get_value() == second_tree->get_value())
		return true;
	
	return false;
}
/*void Tree::swap_Nodes(Node* left_Node, Node* right_Node)
{
	if (left_Node->parent_ == nullptr || right_Node->parent_ == nullptr)
		do_assert("SWAP PROBLEM!\n");

	Node* new_left_Node(right_Node->parent_);
	Node* new_right_Node(left_Node->parent_);

	if (left_Node->parent_->left_ == left_Node)
		left_Node->parent_->left_ = copy_tree(new_left_Node, right_Node);
	if (left_Node->parent_->right_ == left_Node)
		left_Node->parent_->right_ = copy_tree(new_left_Node, right_Node);

	if (right_Node->parent_->left_ == right_Node)
		right_Node->parent_->left_ = copy_tree(new_right_Node, left_Node);
	if (right_Node->parent_->right_ == right_Node)
		right_Node->parent_->right_ = copy_tree(new_right_Node, left_Node);


	destroy(left_Node);
	destroy(right_Node);
}*/


void Tree::destroy_under_Node(Node* current_Node)
{
	size_ -= 2;
	destroy(current_Node->left_);
	destroy(current_Node->right_);
	current_Node->left_ = nullptr;
	current_Node->right_ = nullptr;
}
void Tree::destroy_one_Node(Node* current_Node)
{
	size_--;
	delete current_Node;
}
void Tree::destroy(Node* current_Node)
{
	if (current_Node->left_ != nullptr)
		destroy(current_Node->left_);
	if (current_Node->right_ != nullptr)
		destroy(current_Node->right_);
	
	size_--;
	delete current_Node;
}