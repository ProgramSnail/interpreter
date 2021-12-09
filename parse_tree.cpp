#include "parse_tree.hh"

void CallRuntimeError(const std::string& msg) {
	std::cout << '\n' << msg << '\n';
	exit(1);
	//throw RuntimeError{msg};
}

T ExprNode::execute(ExecuteTag) {
	T ans = T();
	T leftAns = left->execute(ExecuteTag());
	T rightAns = T();
	if (right != nullptr) {
		rightAns = right->execute(ExecuteTag());
	}
	switch (oper) {
		case Operator::NEGATIVE:
			ans = -leftAns;
			break; 
		case Operator::ADD:
			ans = leftAns + rightAns;
			break;
		case Operator::SUB:
			ans = leftAns - rightAns;
			break;
		case Operator::MULT:
			ans = leftAns * rightAns;
			break;
		case Operator::DIV:
			if (rightAns == 0) {
				CallRuntimeError("RE: Divide by zero.");
			}
			ans = leftAns / rightAns;
			break;
		case Operator::MOD:
			if (rightAns == 0) {
				CallRuntimeError("RE: Mod by zero.");
			}
			ans = leftAns % rightAns;
			break;
		default:
			CallRuntimeError("RE: Not recognized operator in expression.");
	}
	return ans;
}

T VarExprNode::execute(ExecuteTag) {
	if (storage->variables.count(id) == 0) {
		CallRuntimeError("RE: Unitialized variable used in expression.");
	}
	return storage->variables[id]; 
}

bool LogicalExprNode::execute(ExecuteTag) {
	bool ans = false;
	bool leftAns = dynamic_cast<LogicalExprNode*>(left)
			->execute(ExecuteTag());
	bool rightAns = false;
	if (right != nullptr) {
		rightAns = dynamic_cast<LogicalExprNode*>(right)
				->execute(ExecuteTag()); 
	}
	switch (oper) {
		case LogicalOperator::NOT:
			ans = !leftAns;
			break;
		case LogicalOperator::AND:
			ans = (leftAns && rightAns);
			break;
		case LogicalOperator::OR:
			ans = (leftAns || rightAns);
			break;
		case LogicalOperator::EQUAL:
			ans = (leftAns == rightAns);
			break;
		case LogicalOperator::NOT_EQUAL:
			ans = (leftAns != rightAns);
			break;
		default:
			CallRuntimeError("RE: Not logical operator in logical expression.");
			break;
	}
	return ans;
}

bool ComparasionNode::execute(ExecuteTag) {
	bool ans = false;
	T leftAns = dynamic_cast<ExprNode*>(left)
			->execute(ExecuteTag());
	T rightAns = dynamic_cast<ExprNode*>(right)
			->execute(ExecuteTag());
	switch (oper) {
		case LogicalOperator::EQUAL:
			ans = (leftAns == rightAns);
			break;
		case LogicalOperator::NOT_EQUAL:
			ans = (leftAns != rightAns);
			break;
		case LogicalOperator::LESS:
			ans = (leftAns < rightAns);
			break;
		case LogicalOperator::GREATHER:
			ans = (leftAns > rightAns);
			break;
		default:
			CallRuntimeError("RE: Not alloved logical operator in comparasion.");
			break;
	}
	return ans;
}

void AssignmentNode::execute() {
	if (storage->variables.count(varId) == 0) {
		CallRuntimeError("RE: assignment to unitialized variable.");
	}
	storage->variables[varId] = expr->execute(ExecuteTag());
}

void CallFuncNode::execute() {
	switch (id) {
		case FuncType::PRINT:
			if (args.size() == 0 || args.size() > 1) {
				CallRuntimeError("RE: Wrong count of arguments in print().");
			}
			try {
				std::cout << dynamic_cast<ExprNode*>(args[0])
						->execute(ExecuteTag());
			} catch (std::bad_cast) {
				CallRuntimeError("RE: Wrong argument type in print().");
			}
			break;
		case FuncType::WRITE:
			if (args.size() == 0 || args.size() > 1) {
				CallRuntimeError("RE: Wrong count of arguments to write().");
			}
			try {
				std::cout << dynamic_cast<StringNode*>(args[0])
						->execute(ExecuteTag());
			} catch(std::bad_cast) {
				CallRuntimeError("RE: Wrong argument type in write()");
			}
			break;
		default:
			CallRuntimeError("RE: Unrecognized function called.");
			break;
	}
}

void CreateVarNode::execute() {
	if (storage->variables.count(id) != 0) {
		CallRuntimeError("RE: Redefenition of existed variable");
	}
	storage->variables[id] = 0;
}