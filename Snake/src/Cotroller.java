import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.ArrayList;

import javax.swing.*;

import org.omg.CORBA.PUBLIC_MEMBER;

public class Cotroller {

	public static void main(String[] args) {
		SnakeFrame frame = new SnakeFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}

class SnakeFrame extends JFrame{
	private SnakePanel snakePanel;
	private static JLabel snake1Label;
	private static JLabel messageLabel;
	private static JLabel snake2Label;
	private JMenuBar menuBar;
	JMenu speedMenu;
	JMenuItem slowItem, midItem, fastItem;
	
	public SnakeFrame() {
		
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

		init();
		
		ActionListener listener = new ActionListener() {
			
			public void actionPerformed(ActionEvent event) {
				if(event.getSource()==slowItem){
					SnakePanel.speed = 600;
				}
				if(event.getSource()==midItem){
					SnakePanel.speed = 400;
				}
				if(event.getSource()==fastItem){
					SnakePanel.speed = 200;
				}
			}
		};
		slowItem.addActionListener(listener);
		midItem.addActionListener(listener);
		fastItem.addActionListener(listener);
	}
	private void init(){
		setTitle("贪吃蛇");
		//设置最小尺寸
		setSize(WIDTH,HEIGHT+20);
		setResizable(false);
		//设置图标
		setIconImage(this.getToolkit().getImage("greenHead.png"));
		//窗口居中
		setLocationRelativeTo(null);
		setLayout(null);
		
		menuBar = new JMenuBar();
        speedMenu = new JMenu("速度");
        slowItem = new JMenuItem("慢");
        midItem = new JMenuItem("中");
        fastItem = new JMenuItem("快");
        speedMenu.add(slowItem);
        speedMenu.add(midItem);
        speedMenu.add(fastItem);
        menuBar.add(speedMenu);
        setJMenuBar(menuBar);
		
		//信息框
		Font labelFont = new Font("黑体",Font.BOLD,30);
		snake1Label = new JLabel("玩家1：3");
		snake1Label.setForeground(Color.RED);
		snake1Label.setFont(labelFont);
		snake1Label.setHorizontalAlignment(JLabel.CENTER);
		snake1Label.setBounds(MESSAGE_X, MESSAGE_Y, 200, MESSAGE_HEIGHT);
		add(snake1Label);
		messageLabel = new JLabel("游戏暂停");
		messageLabel.setForeground(Color.BLACK);
		messageLabel.setFont(labelFont);
		messageLabel.setHorizontalAlignment(JLabel.CENTER);
		messageLabel.setBounds(200, MESSAGE_Y, 650, MESSAGE_HEIGHT);
		add(messageLabel);
		snake2Label = new JLabel("玩家2：3");
		snake2Label.setForeground(Color.GREEN);
		snake2Label.setFont(labelFont);
		snake2Label.setHorizontalAlignment(JLabel.LEFT);
		snake2Label.setBounds(850, MESSAGE_Y, 200, MESSAGE_HEIGHT);
		add(snake2Label);	
		
		//蛇的面板
		snakePanel = new SnakePanel();
		snakePanel.setBounds(MAP_X, MAP_Y, WIDTH, MAP_HEIGHT);
		add(snakePanel);
	}
	
	public static void setSnake1Score(int score){
		snake1Label.setText("玩家1：" + score);
	}
	public static void setSnake2Score(int score){
		snake2Label.setText("玩家2：" + score);
	}
	public static void setMessage(String message){
		messageLabel.setText(message);
	}
	
	public static final int WIDTH = 1015;	//横向可1015/35=29步
	public static final int HEIGHT = 800;	//纵向可700/35=20步
	public static final int MESSAGE_X=0;
	public static final int MESSAGE_Y=0;
	public static final int MESSAGE_HEIGHT=100;
	public static final int MAP_X = 0;
	public static final int MAP_Y = MESSAGE_HEIGHT;
	public static final int MAP_HEIGHT = HEIGHT - MESSAGE_HEIGHT;
}

class SnakePanel extends JPanel implements Runnable{
	Snake snake1, snake2;
	Node food;
	static int speed;
	Thread thread;
	boolean gameIsPause, gameIsOver;
	Image greenHead = this.getToolkit().getImage("greenHead.png");
	Image greenBody = this.getToolkit().getImage("greenBody.png");
	Image redHead = this.getToolkit().getImage("redHead.png");
	Image redBody = this.getToolkit().getImage("redBody.png");
	
	public SnakePanel(){
		
		speed = 600;
		
		newGame();
		
		setBackground(Color.WHITE);
		
		//设置焦点，注册键盘监听器
		setFocusable(true);
		addKeyListener(new KeyAdapter() {
			public void keyPressed(KeyEvent event){
				switch (event.getKeyCode()) {
				case KeyEvent.VK_DOWN:
					snake2.changeDirection(Snake.DOWN);
					break;
				case KeyEvent.VK_S:
					snake1.changeDirection(Snake.DOWN);
					break;
				case KeyEvent.VK_UP:
					snake2.changeDirection(Snake.UP);
					break;
				case KeyEvent.VK_W:
					snake1.changeDirection(Snake.UP);
					break;
				case KeyEvent.VK_LEFT:
					snake2.changeDirection(Snake.LEFT);
					break;
				case KeyEvent.VK_A:
					snake1.changeDirection(Snake.LEFT);
					break;
				case KeyEvent.VK_RIGHT:
					snake2.changeDirection(Snake.RIGHT);
					break;
				case KeyEvent.VK_D:
					snake1.changeDirection(Snake.RIGHT);
					break;
				case KeyEvent.VK_SPACE:
					if(!gameIsOver){
						gamePause();
					}
					break;
				case KeyEvent.VK_ESCAPE:
					if(gameIsOver){
						newGame();
					}
					break;
				default:
					break;
				}
			}
		});
	}
	
	public void newGame(){
		snake1 = new Snake(Snake.RIGHT);
		snake2 = new Snake(Snake.LEFT);
		makeFood();
		gameIsPause = true;
		gameIsOver = false;
		//开启线程
		thread = new Thread(this);
		thread.start();
		
		SnakeFrame.setMessage("新游戏");
		SnakeFrame.setSnake1Score(snake1.score);
		SnakeFrame.setSnake2Score(snake2.score);
		
		repaint();
	}
	
	public void gamePause() {
		if(gameIsPause){
			gameIsPause = false;
			SnakeFrame.setMessage("游戏进行中");
		}else{
			gameIsPause = true;
			SnakeFrame.setMessage("游戏暂停中...");
		}
	}
	
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Node node = null;
    	// 画红蛇
        for (int i = 0; i < snake1.body.size(); i++) {
            g.setColor(Color.RED);
            node = snake1.body.get(i);
            //蛇尾,蛇头与蛇尾重复时（吃食物）不画
            if(i==snake1.body.size()-1 && node.x==snake1.body.get(0).x && node.y==snake1.body.get(0).y){
            	continue;
            }
            if(i==0){
        		g.drawImage(redHead, node.x, node.y, Node.H, Node.W, this);
            }else{
                g.drawImage(redBody, node.x, node.y, Node.H, Node.W, this);
            }
        }
    	// 画绿蛇
        for (int i = 0; i < snake2.body.size(); i++) {
            g.setColor(Color.GREEN);
            node = snake2.body.get(i);
            //蛇尾
            if(i==snake2.body.size()-1 && node.x==snake2.body.get(0).x && node.y==snake2.body.get(0).y){
            	continue;
            }
        	if(i==0){
        		g.drawImage(greenHead, node.x, node.y, Node.H, Node.W, this);
        	}else{
	            g.drawImage(greenBody, node.x, node.y, Node.H, Node.W, this);
        	}
        }
        //画食物
        g.setColor(Color.YELLOW);
        g.fillRoundRect(food.x, food.y, Node.H, Node.W, Node.H, Node.W);
    }

    //计时刷新函数
	public void run() {
		while(!gameIsOver){
			try {
				if(!gameIsPause){
					//蛇移动
					snake1.move();
					snake2.move();
					
					testCollsion();
					testWin();
					eatFood();
					
					//重新绘画
					this.repaint();
					//刷新时间
					Thread.sleep(speed);
				}
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	//检测是否吃到食物
	void eatFood(){
		int fx = food.x;
		int fy = food.y;
		if(snake1.body.get(0).x == fx && snake1.body.get(0).y == fy){
			snake1.body.add(new Node(fx, fy));
			SnakeFrame.setSnake1Score(++snake1.score);
			SnakeFrame.setMessage("玩家1吃到了食物");
			makeFood();
		}else if(snake2.body.get(0).x == fx && snake2.body.get(0).y == fy){
			snake2.body.add(new Node(fx, fy));
			SnakeFrame.setSnake2Score(++snake2.score);
			SnakeFrame.setMessage("玩家2吃到了食物");
			makeFood();
		}
	}
	//检测是否碰撞
	void testCollsion() {
		int s1x = snake1.body.get(0).x;
		int s1y = snake1.body.get(0).y;
		int s2x = snake2.body.get(0).x;
		int s2y = snake2.body.get(0).y;
		//每次检测前先计算本次检测时的蛇身长度，这样在蛇吃掉对方尾巴后不会因为长度+1，而检测新尾巴是否碰撞，
		//因为新尾巴与头是同一个位置，会被误认为咬到了自己
		int s1l = snake1.body.size();
		int s2l = snake2.body.size();
		Node temp = null;
		for(int i=1;i<s1l;i++){
			temp = snake1.body.get(i);
			//是否吃到自己
			if(s1x == temp.x && s1y == temp.y){
				gameIsOver = true;
				SnakeFrame.setMessage("玩家 1 咬到了自己。。。");
			}
			//是否吃到别人
			if(s2x == temp.x && s2y == temp.y){
				//s2吃掉s1的尾巴，s1增加，s2减少
				if(i==snake1.body.size()-1){
					snake2.body.add(new Node(s2x, s2y));
					SnakeFrame.setSnake2Score(++snake2.score);
					snake1.body.remove(i);
					SnakeFrame.setSnake1Score(--snake1.score);
					SnakeFrame.setMessage("玩家2吃掉了玩家1的尾巴~");
				}
				//s2吃到s1的身体，游戏结束
				else{
					gameIsOver = true;
					SnakeFrame.setMessage("玩家2，不能咬别人的身体。。。");
				}
			}
		}
		for(int i=1;i<s2l;i++){
			temp = snake2.body.get(i);
			//是否吃到自己
			if(s2x == temp.x && s2y == temp.y){
				gameIsOver = true;
				SnakeFrame.setMessage("玩家 2 咬到了自己。。。");
			}
			//是否吃到别人
			if(s1x == temp.x && s1y == temp.y){
				//s1吃掉s2的尾巴，s2增加，s1减少
				if(i==snake2.body.size()-1){
					snake1.body.add(new Node(s1x, s1y));
					SnakeFrame.setSnake1Score(++snake1.score);
					snake2.body.remove(i);
					SnakeFrame.setSnake2Score(--snake2.score);
					SnakeFrame.setMessage("玩家1吃掉了玩家2的尾巴~");
				}
				//s1吃到s2的身体，游戏结束
				else{
					gameIsOver = true;
					SnakeFrame.setMessage("玩家1，不能咬别人的身体。。。");
				}
			}
		}
	}
	
	public void testWin() {
		if(snake1.body.size()==1){
			gameIsOver = true;
			SnakeFrame.setMessage("玩家2赢了");
		}
		if(snake2.body.size()==1){
			gameIsOver = true;
			SnakeFrame.setMessage("玩家1赢了");
		}
	}
	
    // 在随机的地方产生食物
    public void makeFood() {
        boolean isInBody = true;
        int x = 0, y = 0;
        int X = 0, Y = 0;
        int i = 0;
        while (isInBody) {
            x = (int) (Math.random() * 29);
            y = (int) (Math.random() * 19);
            X = x * Node.W;
            Y = y * Node.H;
            boolean isFind = false;
            //查找是否在蛇1的身体中
            for (i = 0; i < snake1.body.size(); i++) {
            	if (X == snake1.body.get(i).x && Y == snake1.body.get(i).y){
            		isFind = true;
            		break;
            	}
            }
            //如果没在蛇1中则找蛇2
            if(isFind==false){
	            for (i = 0; i < snake2.body.size(); i++) {
	                if (X == snake2.body.get(i).x && Y == snake2.body.get(i).y){
	                	isFind = true;
	                	break;
	                }
	            }
            }
            //如果都没找到，则不在蛇身体中
            if(!isFind){
	            isInBody = false;
            }
        }
        food = new Node(X, Y);
    }
}

//蛇类
class Snake{
	ArrayList<Node> body;	//蛇身体
	int direction;
	int score;
	boolean isRun = true;
	boolean dirHasChanged = false;	//标志方向是否改变过一次，避免快速按键造成的错误
	
	public Snake(int dir){
		score = 3;
		direction = dir;
		body = new ArrayList<Node>();
		
		//初始化三个蛇身
		if(dir==RIGHT){
			body.add(new Node(SnakeFrame.MAP_X + 2 * Node.W, 0));
			body.add(new Node(SnakeFrame.MAP_X + Node.W, 0));
			body.add(new Node(SnakeFrame.MAP_X, 0));
		}
		if(dir==LEFT){
			body.add(new Node(SnakeFrame.WIDTH - 3*Node.W, SnakeFrame.MAP_HEIGHT - 2*Node.H));
			body.add(new Node(SnakeFrame.WIDTH - 2*Node.W, SnakeFrame.MAP_HEIGHT - 2*Node.H));
			body.add(new Node(SnakeFrame.WIDTH - Node.W, SnakeFrame.MAP_HEIGHT - 2*Node.H));
		}
	}
    
    public void changeDirection(int newDir){
    	//如果新方向与原方向相同或相反，则不改变方向
    	if(dirHasChanged==false && direction%2 != newDir%2){
    		direction = newDir;
    		dirHasChanged = true;
    	}
    }
	
	public void move(){
		if (isRun) {
	        Node node = body.get(0);
	        int X = node.x;
	        int Y = node.y;
	        //蛇头按运行方向前进一个单位
	        switch (direction) {
	        case 1:
	                X -= Node.W;
	                break;
	        case 2:
	                Y -= Node.H;
	                break;
	        case 3:
	                X += Node.W;
	                break;
	        case 4:
	                Y += Node.H;
	                break;
	        }
	        
	        //超出边界则从另一边出来
	        if(X < SnakeFrame.MAP_X){
	        	X = SnakeFrame.WIDTH-Node.W;
	        }else if(X > SnakeFrame.WIDTH-Node.W){
	        	X = SnakeFrame.MAP_X;
	        }else if(Y < 0){
	        	Y = SnakeFrame.MAP_HEIGHT-2*Node.H;
	        }else if(Y > SnakeFrame.MAP_HEIGHT-2*Node.H){
	        	Y = 0;
	        }
	        body.add(0, new Node(X, Y));
	        //去掉蛇尾
	        body.remove(body.size() - 1);
	        
	        dirHasChanged = false;	//置标志：方向可以改变
	    }
	}

    public static final int LEFT = 1;
    public static final int UP = 2;
    public static final int RIGHT = 3;
    public static final int DOWN = 4;
}

//蛇的身体、墙体、食物的基本单位
class Node {
    public static final int W = 35;
    public static final int H = 35;
    int x;
    int y;

    public Node(int x, int y) {
            this.x = x;
            this.y = y;
    }
}