
# Unity 게임 프로그래밍 튜토리얼

## 목차
1. [장애물 런 게임 (RUN)](#장애물-런-게임-run)
2. [GameObject & Script 기초](#gameobject--script-기초)

---

## 장애물 런 게임 (RUN)

### 개발 환경
- Unity 버전: 2019.2.5f1

### 1. 프로젝트 생성

1. Unity Hub 실행 후 '새로 생성' 선택
2. 프로젝트 이름 입력: `RUN` (영문자 권장)
3. 저장 경로 지정
4. 생성 클릭

### 2. 씬 설정

1. `[Assets > Scenes]`의 SampleScene을 `Main`으로 이름 변경

### 3. 에셋 임포트

1. `Window` → `Asset Store`
2. 'standard assets' 검색
3. 'Standard Assets (for Unity…' 다운로드 후 Import
4. None 클릭하여 모든 체크 해제 후 다음 항목만 선택:
   - Cameras
   - Characters
   - CrossPlatformInput
   - Prototyping
   - Utility

**씬 방향 조정**: 원뿔 아이콘을 클릭하여 X는 오른쪽, Y는 위쪽으로 설정

### 4. 스테이지 바닥 만들기

1. `Project` → `Assets` → `Standard Assets` → `Prototyping` → `Prefabs` → `FloorPrototype08x01x08`
2. 이름 변경: `Floor1`
3. Transform 설정:
   - Position: 0, 0, 0
   - Rotation: 0, 0, 0
   - Scale: 1, 1, 1

### 5. 캐릭터 준비

1. `ThirdPersonCharacters` → `Prefabs` → `ThirdPersonController`
2. 이름 변경: `Player`
3. Transform 설정:
   - Position: 0, 0, 0
   - Rotation: 0, 0, 0
   - Scale: 1, 1, 1
4. Inspector → Tag → Player 설정
5. Play 테스트 (a, s, d, f 및 방향키로 조작)

### 6. 카메라 설정

1. `Standard Assets` → `Cameras` → `Prefabs` → `MultipurposeCameraRig` 추가
2. 기존 Main Camera 삭제

### 7. 캐릭터 시작 위치

- Player Transform Position: X:0, Y:0, Z:-1

### 8. 길(바닥) 추가 생성

**Floor2**
- Prefab: FloorPrototype04x01x04
- Position: 0, 0, 12
- Scale: 1, 1, 4

**Floor3**
- Prefab: FloorPrototype08x01x08
- Position: 0, 0, 36
- Scale: 4, 1, 4

**Floor4**
- Prefab: FloorPrototype04x01x04
- Position: 0, 0, 54
- Scale: 1, 1, 1

**BigBlock**
- Prefab: CubePrototype04x04x04
- Position: 0, 0, 36
- Scale: 5, 1, 5

### 9. 스테이지 배경

**Wall1**
- Prefab: PillaPrototype02x08x02
- Position: 32, -10, 36
- Scale: 1, 6, 30

**Wall2** (Wall1 Duplicate)
- Position: -32, -10, 36
- Scale: 1, 6, 30

**Pillar**
- Prefab: JoinInnerPrototype01x06x01
- Position: 0, -15, 100
- Rotation: 0, 315, 0
- Scale: 20, 10, 20

### 10. 장애물 배치

Block1~5 생성 (BlockPrototype04x04x04 Duplicate)

**위치 및 크기**
- Block1: Position(0, 0, 8), Scale(0.5, 0.5, 0.5)
- Block2: Position(12, 0, 24.5), Scale(0.5, 0.5, 0.75)
- Block3: Position(12, 0, 33), Scale(1, 1, 1)
- Block4: Position(-11, 0, 32), Scale(0.5, 0.5, 0.5)
- Block5: Position(-13.5, 0, 38), Scale(0.5, 0.5, 0.5)

### 11. 텍스처 적용

1. Asset Store에서 'Yughues Free Metal Materials' 검색 및 Import
2. 각 오브젝트에 텍스처 적용:
   - Floor1~4: pattern 13 - diffuse
   - Wall1~2: pattern 09 - diffuse
   - Block1~5: pattern 02 - diffuse
   - BigBlock: pattern 10 - diffuse
   - Pillar: pattern 14 - diffuse

### 12. 라이팅 설정

**Directional Light**
- Intensity: 0.2

**Spotlight1**
- Position: 0, 10, 0
- Rotation: 90, 0, 0
- Range: 23, Spot Angle: 50, Intensity: 8

**Spotlight2**
- Position: 0, 11, 24.6
- Range: 25, Spot Angle: 56

**Spotlight3**
- Position: 0, 7.5, 54
- Range: 20, Spot Angle: 34

**Pointlight1**
- Position: -19.2, 6, 32
- Range: 28, Intensity: 8

**Pointlight2**
- Position: 13, 3.5, 39
- Range: 8, Intensity: 6

### 13. 낙하 판정 영역

1. Cube 생성 후 이름 변경: `OutArea`
2. Transform: Position(0, -33, 0), Scale(1000, 1, 1000)
3. Mesh Renderer 제거
4. Box Collider → Is Trigger 체크
5. 스크립트 추가: `Out.cs`

```csharp
// Out.cs 내용은 문서 참조
```

### 14. 목표 지점

1. Cube 생성 후 이름 변경: `GoalArea`
2. Transform: Position(0, 1, 54.5), Scale(4, 2, 3)
3. Mesh Renderer 제거
4. Box Collider → Is Trigger 체크
5. 스크립트 추가: `GoalArea.cs`

### 15. UI 구현

**TimeText**
- UI → Text 생성
- Anchor: left, top
- Position: 90, -20, 0
- Text: "Time : 0"
- Font Size: 22
- Color: Red
- 스크립트: `Timer.cs`

**ResultTitle**
- Text: "Game Result"
- Position: 0, 80, 50
- Font Size: 32
- Alignment: Center
- Color: Red

**ResultTimeText**
- Text: "ResultTime : 0"
- Position: 0, -30, 0
- Font Size: 24
- Color: Sky Blue

**BestTimeText**
- Text: "BestTime : 0"
- Position: 0, 0, 0
- Font Size: 24
- Color: Sky Blue

**RetryButton**
- Text: "Retry?"
- Position: 0, -80, 0
- Size: 160 x 30

### 16. 결과 화면 관리

1. Empty Object 생성: `Result`
2. Canvas 하위에 배치
3. ResultTitle, ResultTimeText, BestTimeText, RetryButton을 Result 하위로 이동
4. Result 비활성화
5. Canvas에 `GameResult.cs` 스크립트 추가
6. Inspector에서 속성 연결

### 17. 사운드 추가

1. Asset Store에서 'Free Music Pack' 다운로드
2. Pillar에 Audio Source 추가
3. AudioClip: Road Hard - Solo
4. Loop 체크
5. Spatial Blend: 1 (3D 사운드)

### 18. 최종 설정

- `Window` → `Rendering` → `Lighting Settings`
- Auto Generate 체크 해제
- Generate Lighting 클릭

---

## GameObject & Script 기초

### 개발 환경
- Unity 버전: 2021.3.6f1

### 1. 기본 스테이지 구성

**Ground 생성**
1. Hierarchy → 3D Object → Cube
2. 이름 변경: `Ground`
3. Transform:
   - Rotation: 10, 0, 0
   - Scale: 20, 1, 70

**카메라 및 라이트**
- Main Camera Position: 0, 11, -52
- Directional Light Position: 40, 23, 40, Rotation: 50, -30, 1

**Material 적용**
1. Create → Material → `GroundMaterial`
2. Albedo에서 원하는 색상 선택
3. Ground에 적용

### 2. 볼 생성

1. 3D Object → Sphere → 이름: `Ball`
2. Position: 0, 15, -30
3. Add Component → Physics → Rigidbody
4. Play 테스트

### 3. 위치 출력 스크립트

**PrtPosition.cs**
```csharp
using UnityEngine;

public class PrtPosition : MonoBehaviour
{
    float startingPoint;
    
    void Start()
    {
        Debug.Log("Start");
        startingPoint = transform.position.z;
    }
    
    void Update()
    {
        float distance = transform.position.z - startingPoint;
        Debug.Log("Distance: " + distance);
    }
}
```

### 4. 조건문 활용

**if문으로 거리 체크**
```csharp
void Update()
{
    float distance = transform.position.z - startingPoint;
    
    if (distance > 40)
        Debug.Log("Over 40: " + distance);
    else if (distance > 20)
        Debug.Log("Over 20: " + distance);
    else
        Debug.Log("Less than 20: " + distance);
}
```

**한 번만 출력하기**
```csharp
bool isOver20 = true;
bool isOver40 = true;

void Update()
{
    float distance = transform.position.z - startingPoint;
    
    if (distance > 40 && isOver40)
    {
        Debug.Log("Over 40 distance: " + distance);
        isOver40 = false;
    }
    else if (distance > 20 && isOver20)
    {
        Debug.Log("Over 20 distance: " + distance);
        isOver20 = false;
    }
}
```

### 5. Collider 활용

**RadiusChange.cs**
```csharp
using UnityEngine;

public class RadiusChange : MonoBehaviour
{
    SphereCollider myCollider;
    
    void Start()
    {
        Rigidbody myRigidbody = GetComponent<Rigidbody>();
        Debug.Log("UseGravity: " + myRigidbody.useGravity);
        myCollider = GetComponent<SphereCollider>();
    }
    
    void Update()
    {
        myCollider.radius += 0.01f;
    }
}
```

### 6. 카메라 추적

**CameraFollow.cs**
```csharp
using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    GameObject ball;
    
    void Start()
    {
        ball = GameObject.Find("Ball");
    }
    
    void Update()
    {
        transform.position = new Vector3(0,
            ball.transform.position.y + 3,
            ball.transform.position.z - 14);
    }
}
```

### 7. 입력 처리

**키보드 입력 - GroundMove.cs**
```csharp
using UnityEngine;

public class GroundMove : MonoBehaviour
{
    void Update()
    {
        float zRotation = transform.localEulerAngles.z;
        zRotation -= Input.GetAxis("Horizontal") * 0.1f;
        transform.localEulerAngles = new Vector3(10, 0, zRotation);
    }
}
```

**마우스 입력 추가**
```csharp
void Update()
{
    // 키보드 입력
    float zRotation = transform.localEulerAngles.z;
    zRotation -= Input.GetAxis("Horizontal") * 0.1f;
    transform.localEulerAngles = new Vector3(10, 0, zRotation);
    
    // 마우스/터치 입력
    if (Input.touchCount > 0 || Input.GetMouseButton(0))
    {
        if (Input.mousePosition.x < Screen.width / 2)
            transform.localEulerAngles = new Vector3(10, 0, 
                transform.localEulerAngles.z + 0.05f);
        else
            transform.localEulerAngles = new Vector3(10, 0, 
                transform.localEulerAngles.z - 0.05f);
    }
}
```

### 8. 물리 Material

**BallBounce 생성**
1. Create → Physic Material → `BallBounce`
2. Bounciness: 0.9
3. Ball의 Sphere Collider Material에 적용
4. Ground의 Box Collider Material에도 적용 (Bounciness: 0.6)

### 9. 점프 구현

**BallJump.cs**
```csharp
using UnityEngine;

public class BallJump : MonoBehaviour
{
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            GetComponent<Rigidbody>().AddForce(Vector3.up * 300);
        }
    }
}
```

### 10. 장애물 구현

**Obstacle 생성**
1. 3D Object → Cylinder → 이름: `Obstacle`
2. Position: 0, 2, -7

**ObstacleMove.cs**
```csharp
using UnityEngine;

public class ObstacleMove : MonoBehaviour
{
    float delta = 0.01f;
    
    void Update()
    {
        float newXPosition = transform.position.x + delta;
        transform.position = new Vector3(newXPosition, 2, -7);
        
        if (transform.position.x < -9)
            delta = 0.01f;
        else if (transform.position.x > 9)
            delta = -0.01f;
    }
}
```

### 11. 부모-자식 구조

**Stage 생성**
1. Create Empty → 이름: `Stage`
2. Position: 0, 0, 0, Rotation: 10, 0, 0
3. Ground와 Obstacle을 Stage 하위로 이동
4. Ground의 GroundMove 스크립트를 Stage로 이동

**LocalPosition 사용**
```csharp
// ObstacleMove.cs 수정
void Update()
{
    float newXPosition = transform.localPosition.x + delta;
    transform.localPosition = new Vector3(newXPosition,
        transform.localPosition.y,
        transform.localPosition.z);
    
    if (transform.localPosition.x < -9)
        delta = 0.01f;
    else if (transform.localPosition.x > 9)
        delta = -0.01f;
}
```

### 12. 충돌 처리

**OnCollisionEnter**
```csharp
void OnCollisionEnter(Collision collision)
{
    Vector3 direction = transform.position - 
        collision.gameObject.transform.position;
    direction = direction.normalized * 1000;
    collision.gameObject.GetComponent<Rigidbody>().AddForce(direction);
}
```

### 13. 씬 재시작

**FailZone 생성**
1. Ground 복사 → 이름: `FailZone`
2. Position: 0, -15, 0
3. Rotation: 20, 0, 0
4. Scale: 100, 1, 200
5. Box Collider → Is Trigger 체크
6. Mesh Renderer 제거

**FailZone.cs**
```csharp
using UnityEngine;
using UnityEngine.SceneManagement;

public class FailZone : MonoBehaviour
{
    void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.name == "Ball")
        {
            SceneManager.LoadScene(0);
        }
    }
}
```

**Build Settings 설정**
- File → Build Settings
- Add Open Scenes
- Build (선택사항)

### 14. 코인 시스템

**Coin 생성**
1. 3D Object → Cylinder → 이름: `Coin`
2. Position: 0, 5, -10
3. Rotation: 110, 0, 0
4. Scale: 1, 0.15, 1
5. Material: Yellow 계열
6. Capsule Collider → Is Trigger 체크

**CoinTrigger.cs**
```csharp
using UnityEngine;

public class CoinTrigger : MonoBehaviour
{
    void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.name == "Ball")
        {
            Destroy(gameObject);
        }
    }
}
```

### 15. Tag 시스템

**Tag 생성 및 적용**
1. Inspector → Tag → Add Tag
2. "Coin" 태그 생성
3. 모든 Coin 오브젝트에 적용

**Tag로 오브젝트 찾기**
```csharp
void Start()
{
    GameObject[] coins = GameObject.FindGameObjectsWithTag("Coin");
    for (int i = 0; i < coins.Length; i++)
    {
        Debug.Log(coins[i].name);
    }
}
```

### 16. 아이템 시스템

**RedCoin 생성**
1. Coin 복사 → 이름: `RedCoin`
2. Material: Red 계열

**RedCoinItem.cs**
```csharp
using UnityEngine;

public class RedCoinItem : MonoBehaviour
{
    void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.name == "Ball")
        {
            DestroyObstacles();
            Destroy(gameObject);
        }
    }
    
    void DestroyObstacles()
    {
        GameObject[] obstacles = 
            GameObject.FindGameObjectsWithTag("Obstacle");
        for (int i = 0; i < obstacles.Length; i++)
        {
            Destroy(obstacles[i]);
        }
    }
}
```

### 17. GameManager 패턴

**GameManager 생성**
1. Create Empty → 이름: `GameManager`

**GameManager.cs**
```csharp
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public int coinCount = 0;
    
    public void RestartGame()
    {
        SceneManager.LoadScene(0);
    }
    
    void RedCoinStart()
    {
        DestroyObstacles();
    }
    
    void DestroyObstacles()
    {
        GameObject[] obstacles = 
            GameObject.FindGameObjectsWithTag("Obstacle");
        for (int i = 0; i < obstacles.Length; i++)
        {
            Destroy(obstacles[i]);
        }
    }
    
    void GetCoin()
    {
        coinCount++;
        Debug.Log("동전 : " + coinCount);
    }
}
```

**다른 스크립트에서 호출**
```csharp
// SendMessage 방식
GameObject.Find("GameManager").SendMessage("RestartGame");

// 직접 접근 방식
GameManager gmComponent = 
    GameObject.Find("GameManager").GetComponent<GameManager>();
gmComponent.RestartGame();
```

### 18. UI 표시

**TextMeshPro 설정**
1. UI → Text (TextMeshPro)
2. Import TMP Essentials

**코인 개수 표시**
```csharp
using TMPro;

public class GameManager : MonoBehaviour
{
    public TextMeshProUGUI coinText;
    
    void GetCoin()
    {
        coinCount++;
        coinText.text = coinCount + "";
    }
}
```

### 19. Prefab 시스템

**Stone Prefab 생성**
1. Stone 오브젝트 생성 및 설정
2. Project 창으로 드래그하여 Prefab 생성
3. Hierarchy에서 삭제

**Stone.cs**
```csharp
using UnityEngine;

public class Stone : MonoBehaviour
{
    Vector3 target;
    
    void Start()
    {
        target = GameObject.Find("Ball").transform.position;
    }
    
    void Update()
    {
        transform.position = Vector3.MoveTowards(
            transform.position, target, 0.01f);
        transform.Rotate(new Vector3(0, 0, 5));
    }
    
    void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.name == "Ball")
        {
            GameManager gmComponent = 
                GameObject.Find("GameManager").GetComponent<GameManager>();
            gmComponent.RestartGame();
        }
    }
}
```

### 20. 발사체 시스템

**Shooter.cs**
```csharp
using UnityEngine;

public class Shooter : MonoBehaviour
{
    public GameObject stone;
    float timeCount = 0;
    
    void Update()
    {
        timeCount += Time.deltaTime;
        if (timeCount > 3)
        {
            Instantiate(stone, transform.position, Quaternion.identity);
            timeCount = 0;
        }
    }
}
```

### 21. 상속

**ObstacleMove 수정**
```csharp
protected void Update()
{
    // 기존 코드
}
```

**Shooter 상속**
```csharp
using UnityEngine;

public class Shooter : ObstacleMove
{
    public GameObject stone;
    float timeCount = 0;
    
    void Update()
    {
        base.Update();  // 부모 클래스 메서드 호출
        
        timeCount += Time.deltaTime;
        if (timeCount > 3)
        {
            Instantiate(stone, transform.position, Quaternion.identity);
            timeCount = 0;
        }
    }
}
```

---

## 주요 개념 정리

### Component
- **Rigidbody**: 물리력의 영향을 받도록 하는 컴포넌트
- **Collider**: 오브젝트의 충돌을 체크하는 컴포넌트
- **Is Trigger**: 물리적 충돌 없이 영역 감지만 수행

### 좌표 시스템
- **position**: 월드 좌표 (전역 좌표)
- **localPosition**: 부모 오브젝트 기준 상대 좌표

### 주요 메서드
- **Start()**: 최초 1회 실행
- **Update()**: 매 프레임마다 실행
- **OnCollisionEnter()**: 물리적 충돌 시 호출
- **OnTriggerEnter()**: Trigger 영역 진입 시 호출

### Access Modifier
- **public**: 다른 클래스에서 접근 가능, Inspector에 표시
- **private**: 클래스 내부에서만 접근 가능 (기본값)
- **protected**: 상속받은 클래스에서 접근 가능

### Time.deltaTime
- 이전 프레임과 현재 프레임 사이의 시간 간격
- 프레임 독립적인 움직임 구현에 사용
