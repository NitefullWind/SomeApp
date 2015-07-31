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
		//�������
		WindowFrame windowFrame = new WindowFrame();
		windowFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		windowFrame.setVisible(true);
	}

}

class WindowFrame extends JFrame implements ActionListener
{

	/**
	 * ���ڿ��
	 */
	private static final long serialVersionUID = 1L;
	
	//����������Ķ���
	Calculator calculator = new Calculator();
	
	//����һ��TextField����Ļ
	private JTextField screen = new JTextField("");
	
	
	public WindowFrame() {
		
		//���ô�����ʽ
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

		setTitle("������");
//		setSize(WIDTH,HEIGHT);
		//������С�ߴ�
		setSize(WIDTH,HEIGHT);
//		setMinimumSize(new Dimension(WIDTH, HEIGHT));
		//����ͼ��
		setIconImage(this.getToolkit().getImage("calculator.png"));
		//���ھ���
		setLocationRelativeTo(null);
		
		//�������
		createPanel();	
		
		//ע����̼�����
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
		//���ý���
		setFocusable(true);
	}
	
	//�������
	void createPanel(){
		
		//������Ļ
		JPanel screenPanel = new JPanel();
		screenPanel.setLayout(new GridLayout(1,1));

		//������Ļ�е�������ʽ
		screen.setFont(new Font("����",Font.BOLD,50));
		//������Ļ������뷽ʽ
		screen.setHorizontalAlignment(JTextField.RIGHT);
		//���ò��ɱ༭
		screen.setEditable(false);
		screen.setBackground(Color.WHITE);
		screenPanel.add(screen);
		
		//��������
		JPanel keysPanel = new JPanel();

		keysPanel.setLayout(new GridLayout(6, 5));

		for(int i=0;i<KEYS.length;i++){
			//��ʼ����ť
			keyBtn[i] = new JButton(KEYS[i]);
			//��ť��������
			keyBtn[i].setFont(new Font("����",Font.BOLD,25));
			//��ťע�������
			keyBtn[i].addActionListener(this);
			//��Ӱ�ť�����
			keysPanel.add(keyBtn[i]);
		}
		
		keyBtn[28].setForeground(Color.RED);
	
		//���ÿ���еĲ���
		setLayout(new BorderLayout());
		
		//�������ӵ����
		Container contentPane = getContentPane();
		contentPane.add(screenPanel,BorderLayout.NORTH);
		contentPane.add(keysPanel);
	}

//	private boolean isNumInput = false;
	private String inputStr = "";
	private String resultStr = "";
	private boolean isCalculated = false;
	
	//���������¼�
	public void actionPerformed(ActionEvent event) {
		
		//��ȡ��ť�ϵ�����
		String label = event.getActionCommand();
		
		//���ڼ�
		if(label.equals("=") && isCalculated==false){
			//������
			resultStr = calculator.calculate(inputStr);
		}
		//�����
		else if(label.equals("C")){
			inputStr = "";
		}
		//�˸��
		else if(label.equals("��")){
			if(isCalculated){
				inputStr = "";
			}else{
				if(inputStr.length()>0){
					inputStr = inputStr.substring(0, inputStr.length()-1);
				}
			}
		}
		//������
		else{
			//��׼��+-���º�������x���
			if((label.equals("��") || label.equals("��"))){
				if(inputStr.length()==0){
					return;
				}
				String last = inputStr.substring(inputStr.length()-1, inputStr.length());
				//���һ���ַ��ǳ˳����Ϊ��ǰ����
				if("����".indexOf(last)>-1) {
					//�����һ���ַ�ȥ��
					inputStr = inputStr.substring(0,inputStr.length()-1);
				}
				//���һ���ַ���+-����������
				else if("+-".indexOf(last)>-1){
					return;
				}
			}
			//��׼��������+��-
			else if(( (label.equals("+")|| label.equals("-") ) && (inputStr.endsWith(label) || inputStr.endsWith("+-") || inputStr.endsWith("-+")))){
					return;
			}
			if(isCalculated){
				inputStr = "";
				//�����������м������ϴεĽ����Ϊ����
				if("+-����^".indexOf(label)>=0){
					inputStr += resultStr;
				}
			}
			inputStr += label;
		}
		
		//���ݰ��������Ƿ񱻼�����ı�־
		if(label=="="){
			//����������ı�־��Ϊ��
			isCalculated = true;
		}else{
			isCalculated = false;
		}
		
		//����Ǻ��������һ������
		if("sincostanlnlog".indexOf(label)>=0){
			inputStr += "(";
		}
		
		//��ʾ����Ļ��
		if(isCalculated){
			screen.setText(inputStr + "=" + resultStr);
		}else{
			screen.setText(inputStr);
		}
	}
	
	private final static int WIDTH = 700;
	private final static int HEIGHT = 450;
	//������ť����
	JButton keyBtn[] = new JButton[KEYS.length];
	private final static String KEYS[] = {
		"!","^","��","��","C",
		"sin","(",")","e","��",
		"cos","7","8","9","��",
		"tan","4","5","6","��",
		"ln","1","2","3","-",
		"log","0",".","=","+"
	};
}

//������
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
		
		//��ʡ�Ե�*�Ų���,�������#��ʾ�ַ�������
		str = pushMulSign(str)+"#";
		
		for(int i=0;i<str.length();i++){
			String s = str.substring(i,i+1);

			//�����������׷�ӵ����ִ�
			if(isNum(s)){
				if(s.equals("��")){
					s = Double.toString(Math.PI);
				}
				if(s.equals("e")){
					s = Double.toString(Math.E);
				}
				numStr += s;
				
				//�������һλ��������
				if(!isNum(str.substring(i+1, i+2))){
					//������ջ
					numStack.push(Double.toString(ZF*Double.valueOf(numStr)));
					ZF = 1;
					//���ִ����
					numStr = "";
				}
			}
			//����������,�Ƚ�������ջ�����жϷ��ŵĲ���
			else if(isSign(s) || s.equals("#")){

				//�����һλ�Ƿ��ţ����ж�����������ѭ��
				if(i==0){
					//����ǡ�-������Ϊ����������Ϊ����
					if(s.equals("-")){
						ZF = -1*ZF;
					}
					continue;
				}
				//����������һλ
				else if(!s.equals("#")){
					//����÷��ź���һλ�ǡ�-����Ϊ����
					if(str.substring(i+1,i+2).equals("-")){
						ZF = -1*ZF;
						i++;
					}else if(str.substring(i+1,i+2).equals("+")){
						i++;
					}
				}
				//�������ջΪ��,��Ϊ"("��ֱ����ջ����ǰ�������ȼ�������ջ
				if(signStack.isEmpty() || s.equals("(") || priority(s)>priority(signStack.lastElement())){
					signStack.push(s);
				}
				//��ǰ�������ȼ�����ջ��Ԫ������
				else{
					//ȡջ��������
					String opStr = signStack.lastElement();
					signStack.pop();
					
					//��������ʱ��ʲôҲ����
					if(s.equals(")") && opStr.equals("(")){
						continue;
					}
					//��Ԫ����������
					else if("+-����^".indexOf(opStr)>=0){
						String a = numStack.lastElement();
						numStack.pop();
						String b = numStack.lastElement();
						numStack.pop();
						
						//����������ջ
						String result = compute(a, b, opStr);
						//������Ϊnull�򷵻ش���
						if(result==null){
							return "����";
						}else
						{
							numStack.push(result);
						}
					}
					//�׳�
					else if(opStr.equals("!")){
						double a = Double.valueOf(numStack.lastElement());
						long LA = (long)a;
						numStack.pop();
						if(a<0 || a!=LA){
							return "����";
						}
						else{
							BigDecimal sum = new BigDecimal("1");
							for(long j=LA;j>0;j--){
								sum = sum.multiply(new BigDecimal(j));
							}
							numStack.push(sum.toString());
						}
					}
					//������,sin,cos,tan,ln,log
					else{
						double a = Double.valueOf(numStack.lastElement());
						numStack.pop();
						if(opStr.equals("sin")){
							numStack.push(Double.toString(Math.sin(a)));
						}else if(opStr.equals("cos")){
							numStack.push(Double.toString(Math.cos(a)));
						}else if(opStr.equals("tan")){
							numStack.push(Double.toString(Math.tan(a)));
						}else if(opStr.equals("��")){
							numStack.push(Double.toString(Math.sqrt(a)));
						}else if(opStr.equals("ln")){
							numStack.push(Double.toString(Math.log(a)));
						}else if(opStr.equals("log")){
							numStack.push(Double.toString(Math.log10(a)));
						}else{
							return "����";
						}
					}
					//��ǰ��������䣬�����Ƚ�
					i--;
					//����ѭ������������Ĳ���
					continue;
				}
			}
//			����sin,cos,tan,log,ln����
			else{
				signStr += s;
				//��signStr����λ�Ժ���ƥ��,��������к���������ֱ����ջ
				if(signStr.equals("ln")|| signStr.length()>2 && "sincostanlog".indexOf(signStr)>=0){
					signStack.push(signStr);
					//�ÿ�signStr
					signStr = "";
				}
			}
			
		}
		//�򵥵���������
		String resultString = numStack.lastElement();
		double result = Double.valueOf(resultString);
		long longResult = (long)result;
		if(result==longResult){
			return Long.toString(longResult);
		}
		return numStack.lastElement();
	}
	
	String compute(String a, String b, String op){
		
		//ʹ��BigDecimal��������������
		BigDecimal bigA =  new BigDecimal(a);
		BigDecimal bigB = new BigDecimal(b);

		if(op.equals("+")) return bigA.add(bigB).toString();
		if(op.equals("-")) return bigB.subtract(bigA).toString();
		if(op.equals("��")) return bigA.multiply(bigB).toString();
		if(op.equals("��")&&!a.equals("0")) return bigB.divide(bigA, MathContext.DECIMAL32).toString();
		if(op.equals("^")){
			double douA = Double.valueOf(a);
			int intA = (int)douA;
			//�����������,����Math.pow����
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
	
	//������ʱʡ�Եġ���ȫ
	String pushMulSign(String str){
		
		StringBuffer stringBuffer = new StringBuffer(str);

		//��Ҫ��ǰ�󶼲�*�ŵķ���
		String sign1[] = {"��","e"};
		for(int i=0;i<sign1.length;i++){
			int index = 0;
			while(index!=-1){
				if(stringBuffer.length()>1 && stringBuffer.substring(0, 1).equals(sign1[i]) && !isSign(stringBuffer.substring(1,2))){
					stringBuffer.insert(++index, "��");
				}
				//�ҳ����ŵ�λ��
				index = stringBuffer.indexOf(sign1[i],index+1);
				if(index!=-1){
					//���ǰ��ȱ����
					if(!isSign(stringBuffer.substring(index-1,index))){
						stringBuffer.insert(index++, "��");
					}
					//�������ȱ����
					if(index!=stringBuffer.length()-1 && !isSign(stringBuffer.substring(index+1,index+2))){
						stringBuffer.insert(++index, "��");
					}
				}
			}
		}
		//ֻ��Ҫ��ǰ�油*�ķ���
		String sign2[] = {"��","sin","cos","tan","ln","log"};
		for(int i=0;i<sign2.length;i++){
			int index = 0;
			while(index!=-1){
				//�ҳ����ŵ�λ��
				index = stringBuffer.indexOf(sign2[i],index+1);
				//������ǵ�һ���ַ���ǰһ���ַ�����+-*/,�����һ��*
				if(index!=-1 && !isSign(stringBuffer.substring(index-1, index))){
					stringBuffer.insert(index++, "��");
				}
			}
		}
		int index=0;
		while(index!=-1){
			index = stringBuffer.indexOf("(",index+1);
			if(index>0 && isNum(stringBuffer.substring(index-1,index))){
				stringBuffer.insert(index, "��");
			}
		}
		index = 0;
		while(index!=-1){
			index = stringBuffer.indexOf(")",index+1);
			//�����һ��λ�ò���
			if(index >0 && index<stringBuffer.length()-1 && isNum(stringBuffer.substring(index+1,index+2))){
				stringBuffer.insert(++index, "��");
			}
		}
		return stringBuffer.toString();
	}
	
	//���ز����������ȼ�
	int priority(String s)
	{
	    if(s.equals("(")||s.equals(")")) return 0;
	    if(s.equals("+")||s.equals("-")) return 1;
	    if(s.equals("��")||s.equals("��")) return 2;
	    if(s.equals("!")||s.equals("^")||s.equals("��")
	    		||s.equals("sin")||s.equals("cos")||s.equals("tan")
	    		||s.equals("ln")||s.equals("log")) return 4;
	    return -1;
	}
	
	boolean isNum(String str){
		if("0123456789��e.".indexOf(str)>=0){
			return true;
		}
		return false;
	}
	boolean isSign(String str){
		if("+-����()^��!".indexOf(str)>=0){
			return true;
		}
		return false;
	}
	
}