#pragma once

#include <cmath>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "storage.hh"

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
	NOT_EQUAL,
	LESS,
	GREATHER
};

enum class FuncType {
	NONE,
	WRITE, // for strings
	// READ, // for strings
	PRINT, // for T
	SCAN // for T
};

using T = int;

struct ExecuteTag {};

struct RuntimeError {
	std::string msg;
};

void CallRuntimeError(const std::string& msg);

class Node;
class RootNode;
class ExprNode;
class NumberExprNode;
class VarExprNode;
class LogicalExprNode;
class ComparasionNode;
class LogicalConstantNode;
class AssignmentNode;
class StringNode;
class CallFuncNode;
class CallTFuncNode;
class BlockNode;
class ConditionNode;
class LoopNode;
class CreateVarNode;


class Node {
public:
	virtual void execute() = 0;
	
	virtual ~Node() {}
};

class RootNode : public Node {
private:
	Node* node;
public:
	
	RootNode(Node* node)
			: node(node) {}
	
	void execute() override {
		node->execute();
	}
	
	~RootNode() {
		if (node) {
			delete node;
		}
	}
};



class ExprNode : public Node {
protected:
	ExprNode* left = nullptr;
	ExprNode* right = nullptr;
	Operator oper = Operator::NONE;
public:
	ExprNode() = default;
	ExprNode(ExprNode* left,
			ExprNode* right, 
			Operator oper) 
			: left(left), right(right), oper(oper) {}

	virtual T execute(ExecuteTag);

	void execute() override {
		execute(ExecuteTag());
	};

	~ExprNode() {
		if (left) {
			delete left;
		}
		if (right) {
			delete right;
		}
	}
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
	Storage* storage = nullptr;
public:
	VarExprNode(const std::string& id, Storage* storage) 
			: id(id), storage(storage) {}
	
	T execute(ExecuteTag) override;
};

class LogicalExprNode : public Node {
protected:
	Node* left = nullptr;
	Node* right = nullptr;
	LogicalOperator oper = LogicalOperator::NONE;
public:
	LogicalExprNode() = default;
	LogicalExprNode(Node* left,
			Node* right, LogicalOperator oper) 
			: left(left), right(right), oper(oper) {}
	
	virtual bool execute(ExecuteTag);

	void execute() override {
		execute(ExecuteTag());
	}

	~LogicalExprNode() {
		if (left) {
			delete left;
		}
		if (right) {
			delete right;
		}
	}
};

class ComparasionNode : public LogicalExprNode {
public:
	ComparasionNode(ExprNode* left,
			ExprNode* right,
			LogicalOperator oper)
			: LogicalExprNode(left, right, oper) {}

	bool execute(ExecuteTag) override;
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
	ExprNode* expr = nullptr;
	Storage* storage = nullptr;
public:
	AssignmentNode(const std::string& varId, 
			ExprNode* expr, Storage* storage) 
			: varId(varId), expr(expr), storage(storage) {}

	void execute() override;

	~AssignmentNode() {
		delete expr;
	}
};

class StringNode : public Node {
private:
	std::string str;
public:
	StringNode(const std::string& tmpStr) : str(tmpStr) {
		str = str.substr(1, str.size() - 2);
		size_t it = 1;
		bool prevIsSlash = false;
		for (size_t i = 1; i < str.size(); ++i, ++it) {
			if (str[it - 1] == '\\' && !prevIsSlash) {
				--it;
				if (str[i] == 'n') {
					str[it] = '\n';
				} else if (str[i] == 't') {
					str[it] = '\t';
				} else if (str[i] == 'r') {
					str[it] = '\r';
				} else if (str[i] == '0') {
					str[it] = '\0';
				} else if (str[i] == '\\'){
					str[it] = '\\';
					prevIsSlash = true;
				} else {
					str[it] = str[i];
					//CallRuntimeError("RE: Unrecognized Special symbol.");
				}
			} else {
				if (it < i) {
					str[it] = str[i];
				}
				prevIsSlash = false;
			}
		}
		str.resize(it);
	}
	
	virtual std::string execute(ExecuteTag) {
		return str;
	}
	
	void execute() override {
		execute(ExecuteTag());
	}
};

class CallFuncNode : public ExprNode {
protected:
	std::vector<Node*> args;
	FuncType id;
	std::istream* in = nullptr;
	std::ostream* out = nullptr;
public:
	CallFuncNode(FuncType id, const std::vector<Node*>& args,
			std::istream& in, std::ostream& out)
			: id(id), args(args), in(&in), out(&out) {}
 	
 	T execute(ExecuteTag) override {
 		CallRuntimeError("RE: Void function in expression");
 		return 0;
 	} 
	
	void execute() override;

	~CallFuncNode() {
		for (size_t i = 0; i < args.size(); ++i) {
			if (args[i]) {
				delete args[i];
			}
		}
	}
};

class CallTFuncNode : public CallFuncNode {
public:
	CallTFuncNode(FuncType id, const std::vector<Node*>& args,
			std::istream& in, std::ostream& out) 
			: CallFuncNode(id, args, in, out) {}

	T execute(ExecuteTag) override {
		size_t ans = 0;
		switch (id) {
			case FuncType::SCAN:
				(*in) >> ans;
				break;
			default:
				CallRuntimeError("RE: Unrecognized or void function used in expression.");
				break;
		}
		return ans;
	} 

	void execute() override {
		execute(ExecuteTag());
	}
};

class BlockNode : public Node {
protected:
	std::vector<Node*> nodes;
public:
	BlockNode(const std::vector<Node*>& nodes) : nodes(nodes) {}
	
	void execute() override {
		for (size_t i = 0; i < nodes.size(); ++i) {
			nodes[i]->execute();
		}
	}

	~BlockNode() {
		for (size_t i = 0; i < nodes.size(); ++i) {
			delete nodes[i];
		}
	}
};

class ConditionNode : public Node {
protected:
	LogicalExprNode* condition = nullptr;
	Node* thenBlock = nullptr;
	Node* elseBlock = nullptr;
public:
	ConditionNode(LogicalExprNode* condition,
			Node* thenBlock, Node* elseBlock) 
			: condition(condition),
				thenBlock(thenBlock),
				elseBlock(elseBlock) {}
	
	void execute() override {
		if (condition->execute(ExecuteTag())) {
			thenBlock->execute();
		} else {
			elseBlock->execute();
		}
	}
	
	~ConditionNode() {
		if (condition) {
			delete condition;
		}
		if (thenBlock) {
			delete thenBlock;
		}
		if (elseBlock) {
			delete elseBlock;
		}
	}
};

class LoopNode : public Node {
protected:
	LogicalExprNode* condition = nullptr;
	Node* doBlock = nullptr;
public:
	LoopNode (LogicalExprNode* condition, Node* doBlock) 
			: condition(condition), doBlock(doBlock) {}
	
	void execute() override {
		while(condition->execute(ExecuteTag())) {
			doBlock->execute();
		} 
	}
	
	~LoopNode() {
		if (condition) {
			delete condition;
		}
		if (doBlock) {
			delete doBlock;
		}
	}
};

class CreateVarNode : public Node {
private:
	std::string id;
	std::vector<std::string> tags;
	Storage* storage = nullptr;
public:
	CreateVarNode(const std::string& id,
			const std::vector<std::string>& tags,
			Storage* storage) 
			: id(id), tags(tags), storage(storage) {}
	
	void execute() override;
};