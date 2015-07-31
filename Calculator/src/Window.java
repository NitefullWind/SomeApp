import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
//import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
//import java.awt.event.KeyAdapter;
import java.awt.event.*;
//import java.awt.event.KeyAdapter;
//import java.awt.event.KeyEvent;
//import java.awt.event.KeyListener;
import java.math.BigDecimal;
import java.math.MathContext;
import java.util.Stack;

import javax.swing.*;

//import com.sun.org.apache.xml.internal.security.keys.content.KeyValue;


public class Window {

	public static void main(String[] args) {
		//声明框架
		WindowFrame windowFrame = new WindowFrame();
		windowFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		windowFrame.setVisible(true);
	}

}

class WindowFrame extends JFrame implements ActionListener
{

	/**
	 * 窗口框架
	 */
	private static final long serialVersionUID = 1L;
	
	//声明计算类的对象
	Calculator calculator = new Calculator();
	
	//声明一个TextField做屏幕
	private JTextField screen = new JTextField("");
	
	
	public WindowFrame() {
		
		//设置窗口样式
		String lookAndFeel = UIManager.getSystemLookAndFeelClassName();
		try {
			UIManager.setLookAndFeel(lookAndFeel);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (UnsupportedLookAndFeelException e) {
			e.printStackTrace();
		}

		setTitle("计算器");
//		setSize(WIDTH,HEIGHT);
		//设置最小尺寸
		setSize(WIDTH,HEIGHT);
//		setMinimumSize(new Dimension(WIDTH, HEIGHT));
		//设置图标
		setIconImage(this.getToolkit().getImage("calculator.png"));
		//窗口居中
		setLocationRelativeTo(null);
		
		//创建面板
		createPanel();	
		
		//注册键盘监听器
		addKeyListener(new KeyAdapter() {
			public void keyPressed(KeyEvent e){
				int code = e.getKeyCode();
				if(code==KeyEvent.VK_0 || code==96){
					keyBtn[26].doClick();
				}else if(code==KeyEvent.VK_PERIOD){
					keyBtn[27].doClick();
				}else if (code==KeyEvent.VK_ENTER) {
					keyBtn[28].doClick();
				}else if (code==KeyEvent.VK_ADD || code==61) {
					keyBtn[29].doClick();
				}else if (code==KeyEvent.VK_1 || code==97) {
					keyBtn[21].doClick();
				}else if (code==KeyEvent.VK_2 || code==98) {
					keyBtn[22].doClick();
				}else if (code==KeyEvent.VK_3 || code==99) {
					keyBtn[23].doClick();
				}else if (code==KeyEvent.VK_SUBTRACT || code==45) {
					keyBtn[24].doClick();
				}else if (code==KeyEvent.VK_4 || code==100) {
					keyBtn[16].doClick();
				}else if (code==KeyEvent.VK_5 || code==101) {
					keyBtn[17].doClick();
				}else if (code==KeyEvent.VK_6 || code==102) {
					keyBtn[18].doClick();
				}else if (code==106) {
					keyBtn[19].doClick();
				}else if (code==KeyEvent.VK_7 || code==103) {
					keyBtn[11].doClick();
				}else if (code==KeyEvent.VK_8 || code==104) {
					keyBtn[12].doClick();
				}else if (code==KeyEvent.VK_9 || code==105) {
					keyBtn[13].doClick();
				}else if (code==111 || code==47) {
					keyBtn[14].doClick();
				}else if (code==KeyEvent.VK_BACK_SPACE) {
					keyBtn[9].doClick();
				}
			}
		});
		//设置焦点
		setFocusable(true);
	}
	
	//创建面板
	void createPanel(){
		
		//声明屏幕
		JPanel screenPanel = new JPanel();
		screenPanel.setLayout(new GridLayout(1,1));

		//设置屏幕中的字体样式
		screen.setFont(new Font("黑体",Font.BOLD,50));
		//设置屏幕字体对齐方式
		screen.setHorizontalAlignment(JTextField.RIGHT);
		//设置不可编辑
		screen.setEditable(false);
		screen.setBackground(Color.WHITE);
		screenPanel.add(screen);
		
		//声明键盘
		JPanel keysPanel = new JPanel();

		keysPanel.setLayout(new GridLayout(6, 5));

		for(int i=0;i<KEYS.length;i++){
			//初始化按钮
			keyBtn[i] = new JButton(KEYS[i]);
			//按钮设置字体
			keyBtn[i].setFont(new Font("黑体",Font.BOLD,25));
			//按钮注册监听器
			keyBtn[i].addActionListener(this);
			//添加按钮到面板
			keysPanel.add(keyBtn[i]);
		}
		
		keyBtn[28].setForeground(Color.RED);
	
		//设置框架中的布局
		setLayout(new BorderLayout());
		
		//将面板添加到框架
		Container contentPane = getContentPane();
		contentPane.add(screenPanel,BorderLayout.NORTH);
		contentPane.add(keysPanel);
	}

//	private boolean isNumInput = false;
	private String inputStr = "";
	private String resultStr = "";
	private boolean isCalculated = false;
	
	//处理输入事件
	public void actionPerformed(ActionEvent event) {
		
		//获取按钮上的文字
		String label = event.getActionCommand();
		
		//等于键
		if(label.equals("=") && isCalculated==false){
			//计算结果
			resultStr = calculator.calculate(inputStr);
		}
		//清除键
		else if(label.equals("C")){
			inputStr = "";
		}
		//退格键
		else if(label.equals("←")){
			if(isCalculated){
				inputStr = "";
			}else{
				if(inputStr.length()>0){
					inputStr = inputStr.substring(0, inputStr.length()-1);
				}
			}
		}
		//其他键
		else{
			//不准在+-×÷后再输入x或÷
			if((label.equals("×") || label.equals("÷"))){
				if(inputStr.length()==0){
					return;
				}
				String last = inputStr.substring(inputStr.length()-1, inputStr.length());
				//最后一个字符是乘除则改为当前符号
				if("×÷".indexOf(last)>-1) {
					//将最后一个字符去掉
					inputStr = inputStr.substring(0,inputStr.length()-1);
				}
				//最后一个字符是+-则不允许输入
				else if("+-".indexOf(last)>-1){
					return;
				}
			}
			//不准连续输入+或-
			else if(( (label.equals("+")|| label.equals("-") ) && (inputStr.endsWith(label) || inputStr.endsWith("+-") || inputStr.endsWith("-+")))){
					return;
			}
			if(isCalculated){
				inputStr = "";
				//如果计算后按下列键，则将上次的结果作为输入
				if("+-×÷^".indexOf(label)>=0){
					inputStr += resultStr;
				}
			}
			inputStr += label;
		}
		
		//根据按键重置是否被计算过的标志
		if(label=="="){
			//将被计算过的标志置为真
			isCalculated = true;
		}else{
			isCalculated = false;
		}
		
		//如果是函数则加上一个括号
		if("sincostanlnlog".indexOf(label)>=0){
			inputStr += "(";
		}
		
		//显示在屏幕上
		if(isCalculated){
			screen.setText(inputStr + "=" + resultStr);
		}else{
			screen.setText(inputStr);
		}
	}
	
	private final static int WIDTH = 700;
	private final static int HEIGHT = 450;
	//声明按钮数组
	JButton keyBtn[] = new JButton[KEYS.length];
	private final static String KEYS[] = {
		"!","^","√","π","C",
		"sin","(",")","e","←",
		"cos","7","8","9","÷",
		"tan","4","5","6","×",
		"ln","1","2","3","-",
		"log","0",".","=","+"
	};
}

//计算类
class Calculator{
	
	public Calculator() {
		
	}
	
	Stack<String> numStack;
	Stack<String> signStack;
	int beginPos=0, endPos=0;
	String numStr, signStr;
//	System.out.println(numStack);
	public String calculate(String str){
		
		numStack = new Stack<String>();
		signStack = new Stack<String>();
		numStr = signStr = "";
		double ZF = 1;
		
		//将省略的*号补齐,且在最后补#表示字符串结束
		str = pushMulSign(str)+"#";
		
		for(int i=0;i<str.length();i++){
			String s = str.substring(i,i+1);

			//如果是数字则追加到数字串
			if(isNum(s)){
				if(s.equals("π")){
					s = Double.toString(Math.PI);
				}
				if(s.equals("e")){
					s = Double.toString(Math.E);
				}
				numStr += s;
				
				//如果后面一位不是数字
				if(!isNum(str.substring(i+1, i+2))){
					//数字入栈
					numStack.push(Double.toString(ZF*Double.valueOf(numStr)));
					ZF = 1;
					//数字串清空
					numStr = "";
				}
			}
			//如果是运算符,先将数字入栈，再判断符号的操作
			else if(isSign(s) || s.equals("#")){

				//如果第一位是符号，则判断正负并跳出循环
				if(i==0){
					//如果是“-”则置为负数，否则为正数
					if(s.equals("-")){
						ZF = -1*ZF;
					}
					continue;
				}
				//如果不是最后一位
				else if(!s.equals("#")){
					//如果该符号后面一位是“-”则为负数
					if(str.substring(i+1,i+2).equals("-")){
						ZF = -1*ZF;
						i++;
					}else if(str.substring(i+1,i+2).equals("+")){
						i++;
					}
				}
				//如果符号栈为空,或为"("则直接入栈，当前符号优先级高则入栈
				if(signStack.isEmpty() || s.equals("(") || priority(s)>priority(signStack.lastElement())){
					signStack.push(s);
				}
				//当前符号优先级低则栈顶元素运算
				else{
					//取栈顶操作符
					String opStr = signStack.lastElement();
					signStack.pop();
					
					//两个括号时，什么也不做
					if(s.equals(")") && opStr.equals("(")){
						continue;
					}
					//二元操作符运算
					else if("+-×÷^".indexOf(opStr)>=0){
						String a = numStack.lastElement();
						numStack.pop();
						String b = numStack.lastElement();
						numStack.pop();
						
						//计算结果并入栈
						String result = compute(a, b, opStr);
						//如果结果为null则返回错误
						if(result==null){
							return "错误";
						}else
						{
							numStack.push(result);
						}
					}
					//阶乘
					else if(opStr.equals("!")){
						double a = Double.valueOf(numStack.lastElement());
						long LA = (long)a;
						numStack.pop();
						if(a<0 || a!=LA){
							return "错误";
						}
						else{
							BigDecimal sum = new BigDecimal("1");
							for(long j=LA;j>0;j--){
								sum = sum.multiply(new BigDecimal(j));
							}
							numStack.push(sum.toString());
						}
					}
					//函数√,sin,cos,tan,ln,log
					else{
						double a = Double.valueOf(numStack.lastElement());
						numStack.pop();
						if(opStr.equals("sin")){
							numStack.push(Double.toString(Math.sin(a)));
						}else if(opStr.equals("cos")){
							numStack.push(Double.toString(Math.cos(a)));
						}else if(opStr.equals("tan")){
							numStack.push(Double.toString(Math.tan(a)));
						}else if(opStr.equals("√")){
							numStack.push(Double.toString(Math.sqrt(a)));
						}else if(opStr.equals("ln")){
							numStack.push(Double.toString(Math.log(a)));
						}else if(opStr.equals("log")){
							numStack.push(Double.toString(Math.log10(a)));
						}else{
							return "错误";
						}
					}
					//当前运算符不变，继续比较
					i--;
					//跳出循环，不做后面的步骤
					continue;
				}
			}
//			处理sin,cos,tan,log,ln函数
			else{
				signStr += s;
				//当signStr是两位以后再匹配,如果是下列函数，可以直接入栈
				if(signStr.equals("ln")|| signStr.length()>2 && "sincostanlog".indexOf(signStr)>=0){
					signStack.push(signStr);
					//置空signStr
					signStr = "";
				}
			}
			
		}
		//简单的四舍五入
		String resultString = numStack.lastElement();
		double result = Double.valueOf(resultString);
		long longResult = (long)result;
		if(result==longResult){
			return Long.toString(longResult);
		}
		return numStack.lastElement();
	}
	
	String compute(String a, String b, String op){
		
		//使用BigDecimal运算解决精度问题
		BigDecimal bigA =  new BigDecimal(a);
		BigDecimal bigB = new BigDecimal(b);

		if(op.equals("+")) return bigA.add(bigB).toString();
		if(op.equals("-")) return bigB.subtract(bigA).toString();
		if(op.equals("×")) return bigA.multiply(bigB).toString();
		if(op.equals("÷")&&!a.equals("0")) return bigB.divide(bigA, MathContext.DECIMAL32).toString();
		if(op.equals("^")){
			double douA = Double.valueOf(a);
			int intA = (int)douA;
			//如果不是整数,则用Math.pow计算
			if(intA!=douA){
				return Double.toString(Math.pow(Double.valueOf(b), Double.valueOf(a)));
			}
			if(intA<0){
				return new BigDecimal("1").divide(bigB.pow(-intA)).toString();
			}
			return bigB.pow(intA).toString();
		}
		return null;
	}
	
	//将输入时省略的×补全
	String pushMulSign(String str){
		
		StringBuffer stringBuffer = new StringBuffer(str);

		//需要在前后都补*号的符号
		String sign1[] = {"π","e"};
		for(int i=0;i<sign1.length;i++){
			int index = 0;
			while(index!=-1){
				if(stringBuffer.length()>1 && stringBuffer.substring(0, 1).equals(sign1[i]) && !isSign(stringBuffer.substring(1,2))){
					stringBuffer.insert(++index, "×");
				}
				//找出符号的位置
				index = stringBuffer.indexOf(sign1[i],index+1);
				if(index!=-1){
					//如果前面缺符号
					if(!isSign(stringBuffer.substring(index-1,index))){
						stringBuffer.insert(index++, "×");
					}
					//如果后面缺符号
					if(index!=stringBuffer.length()-1 && !isSign(stringBuffer.substring(index+1,index+2))){
						stringBuffer.insert(++index, "×");
					}
				}
			}
		}
		//只需要在前面补*的符号
		String sign2[] = {"√","sin","cos","tan","ln","log"};
		for(int i=0;i<sign2.length;i++){
			int index = 0;
			while(index!=-1){
				//找出符号的位置
				index = stringBuffer.indexOf(sign2[i],index+1);
				//如果不是第一个字符且前一个字符不是+-*/,则插入一个*
				if(index!=-1 && !isSign(stringBuffer.substring(index-1, index))){
					stringBuffer.insert(index++, "×");
				}
			}
		}
		int index=0;
		while(index!=-1){
			index = stringBuffer.indexOf("(",index+1);
			if(index>0 && isNum(stringBuffer.substring(index-1,index))){
				stringBuffer.insert(index, "×");
			}
		}
		index = 0;
		while(index!=-1){
			index = stringBuffer.indexOf(")",index+1);
			//在最后一个位置不补
			if(index >0 && index<stringBuffer.length()-1 && isNum(stringBuffer.substring(index+1,index+2))){
				stringBuffer.insert(++index, "×");
			}
		}
		return stringBuffer.toString();
	}
	
	//返回操作符的优先级
	int priority(String s)
	{
	    if(s.equals("(")||s.equals(")")) return 0;
	    if(s.equals("+")||s.equals("-")) return 1;
	    if(s.equals("×")||s.equals("÷")) return 2;
	    if(s.equals("!")||s.equals("^")||s.equals("√")
	    		||s.equals("sin")||s.equals("cos")||s.equals("tan")
	    		||s.equals("ln")||s.equals("log")) return 4;
	    return -1;
	}
	
	boolean isNum(String str){
		if("0123456789πe.".indexOf(str)>=0){
			return true;
		}
		return false;
	}
	boolean isSign(String str){
		if("+-×÷()^√!".indexOf(str)>=0){
			return true;
		}
		return false;
	}
	
}