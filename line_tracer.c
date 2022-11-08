#define Sound A0 //사운드
#define LightR 4 //오른쪽 센서
#define LightL 2 //왼쪽 센서
#define B_1B 5
#define B_1A 6 //오른쪽 모터
#define A_1B 3
#define A_1A 9 //왼쪽 모터

void setup() {
    pinMode(LightL, INPUT);
    pinMode(LightR, INPUT);
    pinMode(A_1A, OUTPUT);
    pinMode(A_1B, OUTPUT);
    pinMode(B_1A, OUTPUT);
    pinMode(B_1B, OUTPUT);
    pinMode(Sound, INPUT);
    while(1) {
        //박수소리 인식 후, 특정 크기보다 크면 탈출
        if(analogRead(Sound)>400) break;
    }
}

void loop()  { 
    if (!digitalRead(LightL) && digitalRead(LightR)) {
        // 왼쪽 센서에 빛이 감지되고(흰색종이) 오른쪽 센서에 감지되지 않으면(검은색종이) 직진
        analogWrite(A_1A, 255);
        analogWrite(A_1B, 0);
        
        analogWrite(B_1A, 255);
        analogWrite(B_1B, 0); 
    } else if (digitalRead(LightL) && digitalRead(LightR)) {  
        // 양쪽 센서에 모두 감지되지 않음 (양쪽 검은색) -> 안쪽 코스로 돌기 위해서는 좌회전 해서 코스 안쪽으로 빠져나와야 하기 때문에 ‘좌회전’
        analogWrite(A_1A, 0);
        analogWrite(A_1B, 180);
        
        analogWrite(B_1A, 255);
        analogWrite(B_1B, 0);
    } else if (!digitalRead(LightL) && !digitalRead(LightR)) {
        //양쪽 센서에 빛 감지(흰색 종이) -> 코스 안쪽으로 탈출했다는 뜻이므로 코스에 다시 걸치기 위해서 ‘우회전’
        analogWrite(A_1A, 255);
        analogWrite(A_1B, 0);
        
        analogWrite(B_1A, 0);
        analogWrite(B_1B, 180);
    } else if (digitalRead(LightL) && !digitalRead(LightR)) {  
        // 코스를 도는 중 코스 바깥쪽으로 나가버리는 경우가 생길 수 있음(왼쪽 센서 검은색, 오른쪽 센서 흰색)  좌회전해서 다시 돌아오기
        analogWrite(A_1A, 0);
        analogWrite(A_1B, 180);

        analogWrite(B_1A, 255);
        analogWrite(B_1B, 0);
    }
}
