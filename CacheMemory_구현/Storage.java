import java.util.StringJoiner;

/*과정 출력을 위한 클래스*/
public abstract class Storage {
    //ram과 Cache의 부모클래스
    int rear;//자료구조 선입선출, 원형큐 자료구조를 응용
    /* 데이터가 들어올때마다 현재 rear 위치 +한칸 위치에 데이터가 삽입,
    rear+1을 MAX로 나눈 나머지 값을 데이터 삽입위치의 인덱스로 사용하면
    가장 오래된 위치의 데이터부터 새로운 데이터로 갱신됨
    (데이터를 삭제하지 않으므로 dequeue를 위한 변수가 필요하지 않음)*/
    final int MAX;//메모리 종류마다 메모리의 사이즈가 다르므로 배열크기를 지정하기 위한 변수
    static float time = 0;//정적변수로 storage를 상속받는 모든 클래스들이 공유하는 변수이다.
    Storage(int max) {
        MAX = max;
        rear = -1;
    }
    abstract void enqueue(int data);//데이터를 삽입하기위한 추상메서드
    abstract int search(int key);//자신이 가진 배열에서 데이터를 찾아 index or data를 반환하는 메서드
    abstract void print(int i);// 특정시점에 저장된 index = i인 곳의 data를 출력하기위한 메서드
}
class Cache extends Storage {
    //Cache 메모리를 위한 클래스
    int[] level;//Cache 메모리를 저장하기위한 배열변수
    static int hit=0;//캐시 히트율을 계산하기 위한 정적 변수
    int cnt=0;//L1만을 위한 변수
    public Cache(int max) {
        super(max);// 매개변수로 주어진 max값을 부모생성자에서 상수인 MAX 의 초기값으로 초기화
        level = new int[MAX];//각 인스턴스의 메모리크기(배열크기)를 초기화된 MAX값으로 지정
    }
    int search(int key) {// key 값 위치의 index를 반환
        time += 0.1;//캐시 접근시간은 L1, L2, L3 모두 0.1초로 동일
        for (int i = 0; i < MAX; i++)//for - 배열 0번째 인덱스부터 끝까지
            if (level[i] == key) {
                // 배열에서 i번째에 있는 값을 key 값과 비교
                hit++;//캐시에 원하는 데이터가 존재하면 hit증가(cache hit)
                status("Hit");//Cache Hit 상태를 출력하기 위한 메서드 호출
                print(i);//캐시 내용을 출력
                return i;// key값과 일치하면 현위치 index를 반환, 아니면 i를 증가하여 반복문 실행
            }
        status("Miss");//Cache Miss 상태를 출력할 메서드 호출
        return -1;// key값과 일치하는 값을 찾지 못한 경우 -1을 반환
    }
    void enqueue(int data) {// 캐시에 data를 삽입하기 위한 메서드
        rear = (rear + 1) % MAX;// rear 위치를 다음 칸으로 이동
        level[rear] = data;// 증가된 위치에 data를 삽입
        print(rear);//data가 저장된 rear 위치와 캐시 내용을 출력
    }
    public void print(int i){
        // 캐시 level에 특정시점에 저장된 데이터를 출력
        System.out.println(this+"\n  index "+i+": "+level[i]);//배열의 i번째 위치에 저장된 데이터
        //배열에 0~10까지 저장된 데이터를 전부 출력
        StringJoiner sj=new StringJoiner(", ","[","]");
        //추가되는 값을 , 로 구분하고 시작과 끝은 [, ]로 나타냄
        try{
            for(int j=0;j<10;j++)
                sj.add(Integer.toString(level[j]));//배열에서 0~10위치의 값들을 한 객체에 담아서 출력
            System.out.println("  "+sj);
            Thread.sleep(3000);// 실행중인 스레드를 일정시간 멈추도록 하는 sleep 메서드
        }catch(InterruptedException e){ }
    }
    void status(String sta){
        try {
            System.out.println(this);//toString 출력, 객체에 대한 정보를 출력
            System.out.println("  status: Cache " + sta);//Hit/Miss 상태 출력
            Thread.sleep(2000);// 실행중인 스레드를 일정시간 멈추도록 하는 sleep 메서드
        }catch(InterruptedException e){ }
    }
    @Override
    public String toString() {
        return "[ L" + (MAX == 5 ? "1" : (MAX == 20 ? "2" : "3")) +
                " Cache ]";// MAX가 5이면 L1 Cache, 20이면 L2, 200이면 L3
    }
}
class Ram extends Storage {
    // RAM과 HDD는 종류가 하나이고 크기가 정해져있으므로 정해진 값으로 초기화
    int[] ram;
    private int[] hdd;// 외부에서 임의로 값을 수정하지 못하도록 설정
    public Ram() {
        super(500);
        ram = new int[MAX];
        hdd = new int[5000];
        for (int i = 1; i <= 5000; i++)// HDD 배열에 1~5000값 저장
            hdd[i - 1] = i;
    }
    int search(int key) {// Ram에서 주어진 key 값을 찾아서 반환
        time += 1;//Ram 접근시간 1초
        for (int i = 0; i < MAX; i++)
            if (ram[i] == key) {
                status("Exist");//ram에서 data를 찾으면 있다고 출력
                print(i);//ram의 내용을 index 0~9까지 출력
                return ram[i];
            }
        status("None");//ram에서 data를 찾지 못한 경우 없다고 출력
        // Ram 에서 key 값을 찾지 못한 경우 HDD 에서 값을 찾기
        System.out.println("[ HDD Access ]");
        time += 3;//HDD 접근시간 3초
        for (int i = 0; i < 5000; i++)
            if (hdd[i] == key) {
                // 하드디스크에서 찾은 key 값을 ram 에 저장 후 break 문으로 반복문 종료
                enqueue(hdd[i]);
                break;
            }
        try{
            Thread.sleep(2000);// 실행중인 스레드를 일정시간 멈추도록 하는 sleep 메서드
        }catch(InterruptedException e){ }
        return ram[rear];// Ram 에서 가장 최근에 삽입된 위치의 값을 반환
    }
    void status(String sta){
        System.out.println(this);//객체 정보 출력
        System.out.println(" status: "+sta);//현재 ram에 찾는 data가 있는지 없는지 나타냄
    }
    void enqueue(int data) {
        // Ram 에 data 를 삽입하기 위한 메서드
        // Hdd 에는 1 ~ 5000 값을 저장해두고 사용하기 위한 배열변수로
        // 생성자에서 배열을 초기화한 후 값의 변경이 일어나지 않는다.
        // (hdd 배열에서는 값을 삽입하는 경우가 존재하지 않으므로 hdd 에 대한 enqueue 는 고려하지 않는다.)
        rear = (rear + 1) % MAX;// rear 위치를 다음 칸으로 이동
        ram[rear] = data;// 증가된 rear 가 가리키는 Ram 위치에 data 를 삽입
        print(rear);//저장된 위치와 data를 출력
    }
    public void print(int i){
        System.out.println(this+"\n  index "+i+": "+ram[i]);
        try{
            Thread.sleep(2000);// 실행중인 스레드를 일정시간 멈추도록 하는 sleep 메서드
        }catch(InterruptedException e){}
    }
    @Override
    public String toString() {
        return "[ Ram ]";
    }
}