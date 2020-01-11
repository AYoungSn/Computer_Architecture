/*과정 출력용 코드*/
public class CacheDemo {
    static Cache L1 = new Cache(5){
        public void print(int i){
            // L1 캐시인 경우 캐시 전체를 출력
            System.out.println(this + "\n  index "+i+"\n  ["
                    + level[0] + ", " + level[1] + ", " + level[2] + ", " + level[3] + ", " + level[4] + "]");
            try {
                Thread.sleep(2000);
            }catch(InterruptedException e){}
        }
        void enqueue(int data) {// 캐시에 data를 삽입하기 위한 메서드
            rear = (rear + 1) % MAX;// rear 위치를 다음 칸으로 이동
            cnt++;//L1 캐시 크기의 두배까지 두 수를 입력받기 위해 L1에 저장되는 횟수를 체크하는 변수
            level[rear] = data;// 증가된 위치에 data를 삽입
            print(rear);//rear 위치에 저장된 data를 출력
        }
    };
    static Cache L2 = new Cache(20);
    static Cache L3 = new Cache(200);
    static Ram ram = new Ram();
    public static void main(String[] args) {
        int R1, R2;
        //R1, R2는 랜덤으로 입력받음
        //L1 캐시 크기의 두배까지 두 수를 입력하여 연산하면서 상태를 출력함
        int i=1;
        while(L1.cnt<10){//L1에 저장한 횟수가 10이하일때까지 반복
            System.out.printf("%d번\n",i++);
            System.out.print("< R1: ");
            R1 = Caching(((int) (Math.random() * 5000)) + 1);
            System.out.print("\n< R2: ");
            R2 = Caching(((int) (Math.random() * 5000)) + 1);
            System.out.println("R1 + R2 = "+(R1 + R2));
            System.out.println();
        }
        System.out.println("Total time: "+ Storage.time);
        System.out.println("Cache Hit rate: "+Cache.hit/(float)L1.cnt);
        System.out.println("Cache hit: "+Cache.hit);

    }
    static int Caching(int key){
        System.out.println(key+" >");//입력된 값을 출력
        int a;
        if((a=L1.search(key))>0) {// L1에 key값이 있는 경우 그 값을 반환, 없으면 다음 if 문(else-if)
            L1.print(a);
            return L1.level[a];
        } else if((a=L2.search(key))>0) {
            // L2에 key 값이 있는 경우 실행
            L1.enqueue(L2.level[a]);// L2에서 찾은 값을 L1에 저장
        }else if((a=L3.search(key))>0){
            // L3에 값이 있는 경우 실행
            L2.enqueue(L3.level[a]);// L3에서 찾은 값을 L2에 저장
            L1.enqueue(L2.level[L2.rear]);//L2에서 찾은 값을 L1에 저장
        }else{
            a=ram.search(key);// Ram에서 key값을 찾는 경우 ram에 없으면 Hdd에서 찾아 ram에 저장하고 그 값을 반환
            L3.enqueue(a);// 찾은 값을 L3에 저장
            L2.enqueue(L3.level[L3.rear]);// L3에서 가장 최근에 저장된 위치의 값을 L2에 저장
            L1.enqueue(L2.level[L2.rear]);// L2에 저장한 값을 L1에 저장
        }
        // 가장 최근에 저장된 위치를 가리키는 변수 = rear
        // rear 가 가리키는 위치의 값을 반환
        // 위의 if문을 모두 실행하고 나면 찾는 값이 L1.rear 위치에 저장되어있다
        return L1.level[L1.rear];
    }
}