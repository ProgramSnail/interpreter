#pragma once

#include <cmath>
#include <string>
#include <vector>
#include <memory>
#include <any>

enum class Operator {
	NONE,
	NEGATIVE, // 
	ADD,
	SUB,
	MULT,
	DIV,
	MOD
};

enum class LogicalOperator {
	NONE,
	NOT, // 
	AND,
	OR,
	EQUAL,
	NOT_EQUAL
};

enum class FuncType {
	WRITE,
	WRITE_STR, 
	READ,
	READ_STR
};

using T = int;

struct ExecuteTag {};

struct RuntimeError {
	std::string msg;
};

class Node {
public:
	virtual void execute();
};

class RootNode : public Node {
	std::unique_ptr<Node> node;
	RootNode(std::unique_ptr<Node>&& node)
			: node(std::move(node)) {}
	void execute() override {
		node->execute();
	}
};



class ExprNode : public Node {
protected:
	std::unique_ptr<ExprNode> left;
	std::unique_ptr<ExprNode> right;
	Operator oper = Operator::NONE;
public:
	ExprNode() = default;
	ExprNode(std::unique_ptr<ExprNode>&& left,
			std::unique_ptr<ExprNode>&& right, 
			Operator oper) 
			: left(std::move(left)),
				right(std::move(right)), oper(oper) {}

	virtual T execute(ExecuteTag) {
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
					throw RuntimeError{"RE: Divide by zero."};
				}
				ans = leftAns / rightAns;
				break;
			case Operator::MOD:
				if (rightAns == 0) {
					throw RuntimeError{"RE: Mod by zero."};
				}
				ans = leftAns % rightAns;
				break;
			default:
				throw RuntimeError{"RE: Not recognized operator in expression."};
		}
		return ans;
	}
	void execute() override {
		execute(ExecuteTag());
	};
};

class NumberExprNode : public ExprNode {
protected:
	T value;
public:
	NumberExprNode(const T& value) : value(value) {}
	T execute(ExecuteTag) override {
		return value;
	};
};

class VarExprNode : public ExprNode {
protected:
	std::string id;
public:
	VarExprNode(const std::string& id) : id(id) {}
	T execute(ExecuteTag) override {
		return T();
		//
		// return values[id]; 
	}
};

class LogicalExprNode : public Node {
protected:
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;
	LogicalOperator oper = LogicalOperator::NONE;
public:
	LogicalExprNode() = default;
	LogicalExprNode(std::unique_ptr<Node>&& left,
			std::unique_ptr<Node>&& right,
			LogicalOperator oper) 
			: left(std::move(left)), 
				right(std::move(right)), oper(oper) {}
	virtual bool execute(ExecuteTag) {
		bool ans = false;
		bool leftAns = dynamic_cast<LogicalExprNode*>(
					left.get())->execute(ExecuteTag());
		bool rightAns = false;
		if (right != nullptr) {
			rightAns = dynamic_cast<LogicalExprNode*>(
					right.get())->execute(ExecuteTag()); 
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
				throw RuntimeError{"RE: Not recognized operator in logical expression."};
				break;
		}
		return ans;
	}
	void execute() override {
		execute(ExecuteTag());
	}
};

class ComparasionNode : public LogicalExprNode {
public:
	ComparasionNode(std::unique_ptr<ExprNode>&& left,
			std::unique_ptr<ExprNode>&& right,
			LogicalOperator oper)
			: LogicalExprNode(std::move(left), std::move(right), oper) {}
	bool execute(ExecuteTag) override {
		bool ans = false;
		T leftAns = dynamic_cast<ExprNode*>(
				left.get())->execute(ExecuteTag());
		T rightAns = dynamic_cast<ExprNode*>(
				right.get())->execute(ExecuteTag());
		switch (oper) {
			case LogicalOperator::EQUAL:
				ans = (leftAns == rightAns);
				break;
			case LogicalOperator::NOT_EQUAL:
				ans = (leftAns != rightAns);
				break;
			default:
				throw RuntimeError{"RE: Not alloved logical operator in comparasion."};
				break;
		}
		return ans;
	}
};

class LogicalConstantNode : public LogicalExprNode {
protected:
	bool value;
public:
	LogicalConstantNode(bool value) : value(value) {}
	bool execute(ExecuteTag) override {
		return value;
	}
};

class AssignmentNode : public Node {
protected:
	std::string varId;
	std::unique_ptr<ExprNode> expr;
public:
	AssignmentNode(const std::string& varId,
			std::unique_ptr<ExprNode>&& expr) 
			: varId(varId), 
				expr(std::move(expr)) {}
	void execute() {
		// value[varId] = expr;
	}
};

class CallFuncNode : public ExprNode {
protected:
	std::vector<std::unique_ptr<Node>> args;
	FuncType id;
public:
	CallFuncNode(FuncType id,
			std::vector<std::unique_ptr<Node>>&& args)
			: id(id), args(std::move(args)) {}
 	T execute(ExecuteTag) override {
 		throw RuntimeError{"RE: Void function in expression"};
 	} 
	void execute() override {
		switch (id) {
		default:
			break;
		}
		//
	}
};

class CallTFuncNode : public CallFuncNode {
public:
	CallTFuncNode(FuncType id,
			std::vector<std::unique_ptr<Node>>&& args) 
			: CallFuncNode(id, std::move(args)) {};
	T execute(ExecuteTag) override {
		switch (id) {
		default:
			break;
		}
		//
		return T();
	} 
	void execute() override {
		execute(ExecuteTag());
	}
};

class BlockNode : public Node {
protected:
	std::vector<std::unique_ptr<Node>> nodes;
public:
	BlockNode(std::vector<std::unique_ptr<Node>>&& nodes) 
			: nodes(std::move(nodes)) {}
	void execute() override {
		for (size_t i = 0; i < nodes.size(); ++i) {
			nodes[i]->execute();
		} 
	}
};

class ConditionNode : public Node {
protected:
	std::unique_ptr<LogicalExprNode> condition;
	std::unique_ptr<Node> thenBlock;
	std::unique_ptr<Node> elseBlock;
public:
	ConditionNode(std::unique_ptr<LogicalExprNode>&& condition,
			std::unique_ptr<Node>&& thenBlock,
			std::unique_ptr<Node>&& elseBlock) 
			: condition(std::move(condition)),
				thenBlock(std::move(thenBlock)),
				elseBlock(std::move(elseBlock)) {}
	void execute() override {
		if (condition->execute(ExecuteTag())) {
			thenBlock->execute();
		} else {
			elseBlock->execute();
		}
	}
};

class LoopNode : public Node {
protected:
	std::unique_ptr<LogicalExprNode> condition;
	std::unique_ptr<Node> doBlock;
public:
	LoopNode (std::unique_ptr<LogicalExprNode>&& condition,
			std::unique_ptr<Node>&& doBlock) 
			: condition(std::move(condition)), 
				doBlock(std::move(doBlock)) {}
	void execute() override {
		while(condition->execute(ExecuteTag())) {
			doBlock->execute();
		} 
	}
};

class CreateVarNode : public Node {
private:
	std::string id;
	std::vector<std::string> tags;
public:
	CreateVarNode(const std::string& id,
			const std::vector<std::string>& tags) 
			: id(id), tags(tags) {}
	void execute() override {
		//
	}
};