
# Unity 게임 프로그래밍 튜토리얼

---

## RollingBall 프로젝트

### 1. 시점 확인하기

**Main Camera 설정**
- Hierarchy → Main Camera 선택
- Inspector → Transform → Position: X:0, Y:0, Z:0

**씬 방향 변경**
- 씬 기즈모의 원뿔 부분을 클릭하여 씬 방향 회전
- X가 오른쪽, Y가 위쪽에 오도록 변경

**Scene 뷰 조작 팁**
- **시점 선회**: Alt + 드래그 (Main Camera 중심으로 회전)
- **시점 평행 이동**: Ctrl + Alt + 드래그 (상하/좌우 이동)
- **줌 업/아웃**: 마우스 휠
- **Object에 시점 맞추기**: F 키 (선택된 Object에 자동 조정)
- **Tool Bar 활용**: Q, W, E, R, T, Y 키

> **참고**: Directional Light는 거리나 위치에 관계없이 한 방향으로 비추는 방향성/지향성 광원

---

### 2. 바닥 만들기

1. **Cube 추가**
   - Hierarchy → Create → 3D Object → Cube

2. **위치 설정**
   - Inspector → Transform → Position: 0, 0, 0

3. **이름 변경**
   - Hierarchy → Cube → Rename → "Floor"

4. **크기 변경**
   - Inspector → Transform → Scale: 10, 0.5, 5

---

### 3. 벽 만들기

**첫 번째 벽 (Wall01)**
1. Hierarchy → Create → 3D Object → Cube
2. Rename → "Wall01"
3. Transform 설정:
   - Position: -5.3, 4.6, 0
   - Scale: 1, 10, 5

**두 번째 벽 (Wall02)**
1. Hierarchy → Wall01 → Duplicate
2. Wall01(1) → Rename → "Wall02"
3. Transform → Position: 5.3, 4.6, 0

**세 번째 벽 (Wall03)**
1. Hierarchy → 3D Object → Cube
2. Rename → "Wall03"
3. Transform 설정:
   - Position: 0, 4.6, 2
   - Scale: 10, 10, 1
4. 씬 기즈모의 사각형 클릭하여 퍼스펙티브 모드로 변경

---

### 4. 카메라와 라이트 변경

**Main Camera**
- Position: 0, 8, -11.9
- Rotation: 18, 0, 0

**Directional Light**
- Position: 0, 0, -11.9
- Rotation: 10, 0, 0

Game 뷰에서 결과 확인

---

### 5. 경사면 만들기

**Slope01**
- Position: -1, 8.57, 1
- Rotation: 0, 0, -10
- Scale: 8, 0.3, 2

**Slope02**
- Slope01 복제
- Position: -1.5, 3.9, 1

**Slope03**
- Slope02 복제
- Position: -3, 0.35, 1
- Scale: 5, 0.3, 2

**Slope04**
- Slope03 복제
- Position: 0.9, 6.2, 1
- Rotation: 0, 0, 8
- Scale: 8, 0.3, 2.2

**Slope05**
- Slope04 복제
- Position: 0.9, 2.2, 1

---

### 6. 공 만들기

1. **Sphere 생성**
   - Hierarchy → 3D Object → Sphere → Rename → "Ball"

2. **Transform 설정**
   - Position: -4.4, 9.58, 0.7
   - Scale: 0.4, 0.4, 0.4

3. **물리 동작 설정**
   - Hierarchy → Ball 선택
   - Component → Physics → Rigidbody 추가
   - Use Gravity 체크

---

### 7. 물리 속성 변경

**Bounce Material 만들기**
1. Project → Create → Physic Material
2. Rename → "Bounce"
3. Inspector → Bounciness: 0.6

**Ball에 적용**
- Hierarchy → Ball
- Inspector → Sphere Collider → Material → Bounce

---

### 8. 공 색상 변경

1. Project → Create → Material → Rename → "Ball"
2. Inspector → Main Maps → Albedo → 원하는 색상 선택
3. Project의 Ball Material을 Hierarchy의 Ball로 드래그

**Play 버튼을 눌러 테스트!**

---

## Character Move

### 1. 게임 리소스 가져오기

1. Menu → Assets → Import Package → Custom Package
2. Chapter4 Terrain.unitypackage 선택
3. Import Unity Package → All → Import

---

### 2. 스크립트 작성

**QueryChanController.cs 생성**

1. Project → Assets → Script 우클릭 → Create → C# Script
2. Rename → "QueryChanController"

```csharp
using UnityEngine;

public class QueryChanController : MonoBehaviour
{
    public float speed = 3.0f;
    public float jumpPower = 6.0f;
    private Vector3 direction;
    private CharacterController controller;
    private Animator anim;

    void Start()
    {
        controller = GetComponent<CharacterController>();
        anim = GetComponent<Animator>();
    }

    void Update()
    {
        float inputX = Input.GetAxis("Horizontal");
        float inputY = Input.GetAxis("Vertical");
        Vector3 inputDirection = new Vector3(inputX, 0, inputY);
        
        direction = Vector3.zero;
        
        if (inputDirection.magnitude > 0.1f)
        {
            transform.LookAt(transform.position + inputDirection);
            direction += transform.forward * speed;
            anim.SetFloat("Speed", direction.magnitude);
        }
        else
        {
            anim.SetFloat("Speed", 0);
        }
        
        if (Input.GetButton("Jump"))
        {
            anim.SetTrigger("Jump");
            direction.y += jumpPower;
        }
        
        controller.Move(direction * Time.deltaTime);
        direction.y += Physics.gravity.y * Time.deltaTime;
    }
}
```

**스크립트 적용**
- Project → Assets → PQchan(prefab) → Inspector → Open
- Script 컴포넌트에 QueryChanController 추가

---

### 3. 스테이지 만들기

**터레인 추가 및 설정**
1. Hierarchy → 3D Object → Terrain
2. Terrain Settings:
   - Terrain Width: 100
   - Terrain Length: 100

**카메라 설정**
- Main Camera Position: 53, 26.5, -4
- Main Camera Rotation: 41.7, 0, 0

---

### 4. 터레인 텍스처링

**잔디 텍스처**
1. Hierarchy → Terrain
2. Inspector → Terrain → Paint Terrain → Paint Texture
3. Edit Terrain Layers → Create Layer → Grass

**모래 텍스처 추가**
1. Edit Terrain Layers → Create Layer → Sand
2. Sand Layer 선택
3. Brush Size: 20, Opacity: 20
4. '[' 와 ']' 키로 브러시 크기 조절
5. Scene에서 클릭하여 페인팅

---

### 5. 지형 편집

**산 만들기**
1. Paint Terrain → Raise or Lower Terrain
2. Brush Size & Opacity 조절
3. Scene에서 클릭하여 지형 높이 조절

---

### 6. 캐릭터 배치 및 테스트

1. Project → Assets → PQchan을 Hierarchy로 드래그
2. PQchan Transform:
   - Position: 50, 0.2, 50
3. Main Camera Transform:
   - Position: 50, 2.5, 46

#### Main Camera Transform 상세 설명

**Transform이란?**
- Unity에서 모든 GameObject의 위치, 회전, 크기를 제어하는 컴포넌트
- 3가지 주요 속성으로 구성됨

**Position (위치)**
- **X축**: 좌(-) / 우(+) 방향
- **Y축**: 아래(-) / 위(+) 방향 (높이)
- **Z축**: 뒤(-) / 앞(+) 방향
- Position: 50, 2.5, 46의 의미:
  - X: 50 → 터레인 중앙 부근 (터레인이 100x100이므로)
  - Y: 2.5 → 지면에서 2.5 유닛 위 (캐릭터 뒤에서 살짝 높은 각도)
  - Z: 46 → 캐릭터(50)보다 4유닛 뒤쪽

**Rotation (회전)**
- **X축 회전**: 위/아래로 고개 숙이기 (Pitch)
- **Y축 회전**: 좌/우로 고개 돌리기 (Yaw)
- **Z축 회전**: 머리 좌우로 기울이기 (Roll)
- 각도는 0~360도 사용

**Scale (크기)**
- 카메라는 일반적으로 Scale을 변경하지 않음 (1, 1, 1 유지)

**이 설정의 효과**
- 캐릭터 뒤쪽 약간 높은 위치에서 캐릭터를 따라가는 3인칭 시점
- 캐릭터(50, 0.2, 50)와 카메라(50, 2.5, 46)의 관계:
  - X: 같은 값(50) → 좌우 중앙 정렬
  - Y: 2.3 차이 → 캐릭터보다 높은 위치
  - Z: 4 차이 → 캐릭터 뒤쪽에 위치

**조작 방법**
- 방향키: 이동
- Space bar: 점프

