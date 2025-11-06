# 웹 어셈블리(WebAssembly)를 사용하여 C++ 코드 실행하기

이 문서는 웹 어셈블리(Wasm)의 개념을 이해하고, C++로 작성된 코드를 웹 어셈블리로 컴파일하여 웹 브라우저에서 실행하는 과정을 단계별로 안내합니다.

---

### 1단계: 웹 어셈블리란?

웹 어셈블리는 웹 브라우저에서 실행할 수 있는 새로운 유형의 코드입니다. 텍스트 기반의 웹 기술(HTML, CSS, JavaScript)과 함께 작동하며, 네이티브에 가까운 성능으로 코드를 실행할 수 있게 해주는 바이너리 형식의 저수준 언어입니다.

주요 특징은 다음과 같습니다.

-   **성능**: JavaScript보다 훨씬 빠르게 코드를 파싱하고 실행할 수 있어 계산 집약적인 작업(게임, 3D 렌더링, 비디오 편집 등)에 유리합니다.
-   **이식성**: C, C++, Rust 등 다양한 언어로 작성된 코드를 웹에서 실행할 수 있도록 컴파일할 수 있습니다.
-   **보안**: 웹 브라우저의 보안 샌드박스 내에서 실행되므로 시스템에 직접 접근할 수 없습니다.

---

### 2단계: 개발 환경 설정 (Emscripten)

C++ 코드를 웹 어셈블리로 컴파일하려면 **Emscripten**이라는 도구가 필요합니다. Emscripten은 C/C++ 코드를 Wasm으로 변환해주는 컴파일러 툴체인입니다.

**설치 방법:**

1.  **Git**이 설치되어 있는지 확인합니다.
2.  터미널에서 다음 명령어를 실행하여 Emscripten SDK를 설치합니다.

    ```bash
    # 1. 저장소 복제
    git clone https://github.com/emscripten-core/emsdk.git

    # 2. emsdk 디렉토리로 이동
    cd emsdk

    # 3. 최신 SDK 설치
    ./emsdk install latest

    # 4. 최신 SDK 활성화
    ./emsdk activate latest

    # 5. 현재 터미널 세션의 환경 변수 설정
    source ./emsdk_env.sh
    ```

    **참고**: 새 터미널을 열 때마다 `source ./emsdk_env.sh`를 실행하여 Emscripten 환경을 활성화해야 합니다.


---
![설치과정 1](<img/01_WebAssembly_Start/Pasted image 20251106133736.png>)

![설치과정 2](<img/01_WebAssembly_Start/Pasted image 20251106133750.png>)
---

### 3단계: 간단한 C++ 코드 작성하기

웹 어셈블리로 컴파일할 간단한 C++ 파일을 작성합니다. `hello.cpp`라는 이름으로 파일을 생성하고 다음 코드를 추가합니다.

![파일 생성](<img/01_WebAssembly_Start/Pasted image 20251106134119.png>)


**`hello.cpp`**
```cpp
#include <iostream>

int main() {
    std::cout << "Hello, WebAssembly from C++!" << std::endl;
    return 0;
}
```

![코드 내용](<img/01_WebAssembly_Start/Pasted image 20251106134130.png>)

이 코드는 콘솔에 간단한 인사말을 출력합니다.

---

### 4단계: C++ 코드를 웹 어셈블리로 컴파일하기

이제 Emscripten 컴파일러(`emcc`)를 사용하여 C++ 파일을 웹 어셈블리로 컴파일합니다.

터미널에서 다음 명령어를 실행하세요.

```bash
emcc hello.cpp -o hello.html
```

![컴파일 과정](<img/01_WebAssembly_Start/Pasted image 20251106134229.png>)

이 명령어는 다음 세 가지 파일을 생성합니다.

1.  **`hello.wasm`**: 컴파일된 웹 어셈블리 모듈입니다. 실제 C++ 코드가 변환된 바이너리 파일입니다.
2.  **`hello.js`**: Wasm 모듈을 로드하고 실행하는 "접착제(glue)" 역할을 하는 JavaScript 파일입니다.
3.  **`hello.html`**: Wasm 코드를 실행하는 데 필요한 모든 것을 담고 있는 HTML 파일입니다.

`emcc`는 컴파일 과정을 단순화하여 웹 환경에서 바로 실행할 수 있도록 HTML 파일까지 자동으로 생성해줍니다.

---

### 5단계: 웹 서버에서 결과 확인하기

보안상의 이유로 웹 브라우저는 로컬 파일 시스템에서 직접 웹 어셈블리 파일을 실행하는 것을 제한합니다. 따라서 로컬 웹 서버를 실행하여 `hello.html` 파일을 열어야 합니다.

Python이 설치되어 있다면 간단한 웹 서버를 실행할 수 있습니다.

1.  `hello.html` 파일이 있는 디렉토리에서 터미널을 엽니다.
2.  다음 명령어를 실행하여 웹 서버를 시작합니다.

    ```bash
    # Python 3
    python3 -m http.server 8000
    ```

3.  웹 브라우저를 열고 주소창에 `http://localhost:8000/hello.html`을 입력합니다.

브라우저가 열리면 개발자 도구의 콘솔(F12 키)에서 "Hello, WebAssembly from C++!"라는 메시지를 확인할 수 있습니다. 이 메시지는 C++ 코드가 웹 어셈블리로 성공적으로 변환되어 브라우저에서 실행되었음을 의미합니다.

![브라우저 출력](<img/01_WebAssembly_Start/Pasted image 20251106134358.png>)
