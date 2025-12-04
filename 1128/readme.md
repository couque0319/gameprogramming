
# 📘 언리얼 엔진 5 비기너 튜토리얼 가이드

## EP1. 언리얼 엔진 설치 및 실행

### 🔹 1. Epic Games Launcher 설치

- Epic Games 공식 사이트 접속
- Download 버튼 클릭 후 런처 설치
- 로그인 또는 회원가입 후 실행

### 🔹 2. 언리얼 엔진 다운로드

- 런처 실행 → 좌측 메뉴 **Unreal Engine** 선택
- 상단 탭 **Library**에서 엔진 버전 선택
- 원하는 버전 설치 (Install)
- **옵션(Options)** 버튼에서 추가 컴포넌트 선택 가능

### 🔹 3. 프로젝트 브라우저

- **Launch** 버튼 클릭 → Unreal Project Browser 실행
- 좌측 카테고리에서 **GAMES** 선택 → 템플릿 선택
- 프로젝트 이름 입력 후 생성

### 🔹 4. 템플릿 종류 (요약)

- **게임용**: First Person, Third Person, Top Down, VR, Vehicle 등
- **영상/가상 제작**: Virtual Production, Motion Design, InCameraVFX 등
- **건축용**: Archviz, Design Configurator, Collab Viewer
- **자동차/제품 디자인**: Photo Studio, Production Configuration 등

---

## EP2. 프로젝트 생성과 기본 인터페이스

### 🔹 1. Third Person Template 생성

- 프로젝트 기본 설정(품질, 위치, C++ 여부 등) 선택 후 생성
- UE4 레이아웃 / UE5 레이아웃 중 편한 레이아웃 선택 가능

### 🔹 2. 언리얼 엔진 화면 구성

**주요 UI 요소**

- **뷰포트(Viewport)** – 게임 화면 및 오브젝트 배치
- **메뉴바·툴바** – 엔진 기능 제어
- **아웃라이너(Outliner)** – 오브젝트 계층 구조
- **디테일 패널(Details)** – 선택한 오브젝트의 상세 설정
- **콘텐츠 브라우저(Content Browser)** – 파일 및 애셋 관리
- **액터 배치(Place Actors)** – 기본 오브젝트 삽입 패널

**단축키**: `Ctrl + Space` → 콘텐츠 브라우저 열기/닫기

### 🔹 3. 기본 조작법

- **우클릭 + WASD** → 카메라 이동
- **Q/W/E/R** → 선택/이동/회전/스케일
- 스냅 기능 On/Off 가능
- 카메라 속도 조절 가능

### 🔹 4. 레벨 생성

- 콘텐츠 브라우저에서 폴더 생성
- 우클릭 → Level 생성
- 더블클릭하여 레벨 열기

### 🔹 5. 환경 조명 추가

**방법 1: 환경 라이트 믹서(Recommended)**

- Sky Light
- Directional Light (태양광)
- Sky Atmosphere
- Volumetric Cloud
- Exponential Height Fog

**방법 2: Place Actors 패널에서 직접 배치**

---

## EP3. 블루프린트 기초

### 🔹 1. 스크립트 종류

#### ① Level Blueprint
- 전체 레벨 단위 로직 작성

#### ② Actor Blueprint
- 콘텐츠 브라우저에서 Blueprint Class → Actor 생성

### 🔹 2. 블루프린트 창 구성

- **상태창** – 변수, 함수, 이벤트 목록
- **이벤트 그래프(Event Graph)** – 실제 로직 작성 구역
- **디테일 패널** – 선택한 노드 설정 변경

### EP3 실습: 키보드 누르면 화면에 문구 띄우기

#### 🔹 1. Input Action 생성

- 콘텐츠 브라우저에서 Input Action 생성
- IMC_Default 매핑 컨텍스트에서 새 슬롯 추가
- 원하는 키를 등록 (예: 키보드 F 키)

#### 🔹 2. 블루프린트 이벤트 그래프에서 처리

- InputAction 이벤트 → PrintString 연결
- 실행 시 키 입력하면 화면에 문구 출력

### EP3 Advanced: 움직이는 도형 만들기

- Enhanced Input 시스템 활용
- Move Action 생성 후 X/Y 값 매핑
- Pawn의 Movement Component 설정
- SpringArm + Camera 부착

---

## EP4. C++ 개발 기초

### 🔹 1. Visual Studio 설치

- Visual Studio 설치 → **C++을 사용한 게임 개발** 워크로드 선택
- UE5에서 Tools → Open Visual Studio 실행

### 🔹 2. C++ 프로젝트 구성 파일 설명

#### MyActor.h

- **CoreMinimal.h**: UE 핵심 기능
- **Actor.h**: Actor 클래스 기본 기능
- **클래스명.generated.h**: 반드시 마지막에 위치해야 함

#### MyActor.cpp

- **BeginPlay()** – 시작 시 1회 실행
- **Tick()** – 매 프레임 실행

### 🔹 3. C++로 화면에 문구 띄우기

- 함수 작성 → `GEngine->AddOnScreenDebugMessage()` 호출
- Actor를 블루프린트로 변환 후 레벨에 배치하면 동작

### 🔹 4. Visual Studio 관련 버그 해결

**라이브 코딩 링크 오류 발생 시**

- Saved 폴더 삭제
- UE5와 VS 모두 재시작

---

## EP5. 샘플 & 애셋 사용법

### 🔹 1. 샘플 프로젝트 다운로드

- Epic Games Launcher → **샘플** 탭
- 콘텐츠 예제 선택 → 라이브러리에 추가
- 프로젝트 생성 버튼으로 다운로드

### 🔹 2. 무료 애셋 다운로드

- **Fab** 탭에서 '모든 애셋' 선택
- Tag → **무료** 필터 적용
- 원하는 애셋 선택 후 프로젝트에 추가

### 🔹 3. 애셋을 이용해 레벨 꾸미기

- 콘텐츠 브라우저 폴더 형태로 자동 추가
- 드래그 앤 드롭으로 레벨 구성

---

## ✔ 전체 요약

이 가이드는 언리얼 엔진 입문자가 다음을 익히도록 구성되어 있습니다:

1. **설치 → 실행 → 프로젝트 생성 → UI 이해 → 기본 조작**
2. **블루프린트 기초 → 입력 시스템 → 간단한 기능 구현**
3. **C++ 기초 구조 이해 및 Actor 클래스 생성법**
4. **샘플 활용 및 무료 애셋 가져오기**
