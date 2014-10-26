/*
 * #!/usr/bin/env python
 * # coding=utf-8
 */

package y14.swct.calculator;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.StreamTokenizer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Stack;

/**
 *
 * @author dengxt
 */
public class Caculator {

    private static final Map<Character, Operator> operators;

    static {
	operators = new HashMap<>();
	for (Operator op : Operator.values()) {
	    operators.put(op.token, op);
	}
    }

    public static StreamTokenizer in;

    public static int readInt() throws IOException {
	int nextToken = in.nextToken();
	return (int) in.nval;
    }

    public static String readStr() throws IOException {
	in.nextToken();
	return (String) in.sval;
    }

    public static void main(String[] args) throws IOException {

//	InputStreamReader reader = new InputStreamReader(System.in);
	FileReader reader = new FileReader("D:\\calculator_TC.txt");
	BufferedReader br = new BufferedReader(reader);
	in = new StreamTokenizer(br);

	int tc = 10;
	for (int test_case = 0; test_case < tc; test_case++) {
	    
	    int size = Integer.valueOf(br.readLine());
	    String expr = br.readLine();
	    List<Character> postOrder = getPostOrder(expr);
	    Expression e = parse(postOrder);
	    int result = e.accept(new Evaluator());
	    System.out.printf("#%d %d\n", test_case + 1, result);
	}

    }

    public static Expression parse(List<Character> postOrder) {

	Stack<Expression> stack = new Stack<>();

	postOrder.stream().forEach((token) -> {

	    if ('0' <= token && token <= '9') {
		stack.push(new NumericExpr(token - 48));
	    } else if (token == '*' || token == '+') {
		Operator op = operators.get(token);
		Expression exprR = stack.pop(), exprL = stack.pop();
		stack.push(new OperationExpr(exprL, exprR, op));
	    }
	});

	return stack.pop();
    }

    public static List<Character> getPostOrder(String expression) {

	Stack<Character> stack = new Stack<>();
	List<Character> postOrder = new ArrayList(expression.length());
	int len = expression.length();

	for (int i = 0; i < len; i++) {
	    
	    char c = expression.charAt(i);
	    
	    if ('0' <= c && c <= '9') {
		postOrder.add(c);
	    } else if (c == '(' || c == ')') {
		handleBrace(c, stack, postOrder);
	    } else if (c == '*' || c == '+') {
		handleOperator(c, stack, postOrder);
	    }
	 }
	
	while(!stack.isEmpty()){
	    char c = stack.pop();
	    if(c != '(') postOrder.add(c);
	}

	return postOrder;
    }
    

    private static void handleOperator(char token, Stack<Character> stack, List<Character> postOrder) {
	
	if(stack.isEmpty()){
	    stack.push(token);
	    return;
	}

	Operator op = operators.get(token);
	
	char c = stack.lastElement();
	Operator top = operators.get(c);


	while (top != null && op.ord() <= top.ord()) {
	    
	    postOrder.add(stack.pop());
	    
	    if(stack.isEmpty()) break;
	    
	    c = stack.lastElement();
	    top = operators.get(c);
	}
	
	stack.push(token);
    }

    private static void handleBrace(char token, Stack<Character> stack, List<Character> postOrder) {

	if (token == '(') {
	    stack.push('(');
	} else if (token == ')') {

	    char expr;

	    while (!stack.isEmpty() && (expr = stack.pop()) != '(') {
		postOrder.add(expr);
	    }
	}
    }

    public static class Evaluator implements ExpressionVisitor<Integer> {

	@Override
	public Integer visitNumber(NumericExpr expression) {
	    return expression.getValue();
	}

	@Override
	public Integer visitOperation(OperationExpr expression) {
	    return expression.getOp().eval(expression.exprL().accept(this), expression.exprR().accept(this));
	}

	@Override
	public Integer visitBrace(BraceExpr expr) {
	    return 0;
	}

    }

    public interface ExpressionVisitor<A> {

	A visitNumber(NumericExpr expr);

	A visitOperation(OperationExpr expr);

	A visitBrace(BraceExpr expr);
    }

    public interface Expression {

	<A> A accept(ExpressionVisitor<A> visitor);
    }

    public static class NumericExpr implements Expression {

	private final int value;

	public NumericExpr(int value) {
	    this.value = value;
	}

	public int getValue() {
	    return value;
	}

	@Override
	public <A> A accept(ExpressionVisitor<A> visitor) {
	    return visitor.visitNumber(this);
	}
    }

    public static class OperationExpr implements Expression {

	private Expression exprL, exprR;

	private Operator op;

	public OperationExpr(Operator op) {
	    this.op = op;
	}

	public OperationExpr(Expression exprL, Expression exprR, Operator op) {
	    this.exprL = exprL;
	    this.exprR = exprR;
	    this.op = op;
	}

	public void setExprL(Expression exprL) {
	    this.exprL = exprL;
	}

	public void setExprR(Expression exprR) {
	    this.exprR = exprR;
	}

	public Expression exprL() {
	    return exprL;
	}

	public Expression exprR() {
	    return exprR;
	}

	public Operator getOp() {
	    return op;
	}

	@Override
	public <A> A accept(ExpressionVisitor<A> visitor) {
	    return visitor.visitOperation(this);
	}
    }

    public static class BraceExpr implements Expression {

	public BraceExpr() {

	}

	@Override
	public <A> A accept(ExpressionVisitor<A> visitor) {
	    return visitor.visitBrace(this);
	}
    }

    public enum Operator {

	ADD('+') {
		    @Override
		    public int eval(int exprL, int exprR) {
			return exprL + exprR;
		    }
		    
		    @Override
		    public int ord() {
			return 1;
		    }
		},
	MULTIPLY('*') {
		    @Override
		    public int eval(int exprL, int exprR) {
			return exprL * exprR;
		    }
		    
		    @Override
		    public int ord() {
			return 2;
		    }
		};

	private final char token;

	private Operator(char token) {
	    this.token = token;
	}

	@Override
	public String toString() {
	    return token + "";
	}

	abstract public int eval(int exprL, int exprR);
	
	abstract public int ord();
    }
}
