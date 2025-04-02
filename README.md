# 🐚 Jetty_minishell

[![GitHub stars](https://img.shields.io/github/stars/DawnteaStudio/Jetty_minishell?style=social)](https://github.com/DawnteaStudio/Jetty_minishell/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/DawnteaStudio/Jetty_minishell?style=social)](https://github.com/DawnteaStudio/Jetty_minishell/network)
[![GitHub license](https://img.shields.io/github/license/DawnteaStudio/Jetty_minishell)](https://github.com/DawnteaStudio/Jetty_minishell/blob/main/LICENSE)
[![GitHub last commit](https://img.shields.io/github/last-commit/DawnteaStudio/Jetty_minishell)](https://github.com/DawnteaStudio/Jetty_minishell/commits/main)

> “나만의 셸을 직접 구현해보며 시스템 프로그래밍의 본질을 배웠습니다.”  
> _- by sewopark && erho

---

## 📌 주요 기능

- 사용자 입력 파싱 및 실행
- 파이프 (`|`) 및 리디렉션 (`>`, `<`, `>>`) 처리
- 환경 변수 (`$VAR`) 치환 기능
- built-in 명령어 (`cd`, `echo`, `exit`, `export`, ...) 직접 구현
- 시그널 처리 (`Ctrl+C`, `Ctrl+\`) 및 에러 메시지 출력
- fork/execve 기반 다중 프로세스 처리
- 메모리 누수 없이 안정적인 셸 실행

---

## ⚙️ 실행 방법

```bash
$ git clone https://github.com/DawnteaStudio/Jetty_minishell.git
$ cd Jetty_minishell
$ make
$ ./minishell
```

---

## 🧠 핵심 구현 포인트

- **파싱기 구현**: 토큰 분리, 인용부호 처리, 환경변수 파싱 등 복잡한 문법 해석
- **프로세스 제어**: pipe를 활용한 자식 프로세스 실행 및 연결
- **가비지 컬렉터**: 연결리스트 기반의 미니 GC를 통해 메모리 누수 방지
- **시그널 분기 처리**: 부모와 자식 프로세스에서의 시그널 처리 분리

---

## 🧩 트러블슈팅 사례

### 🔸 메모리 누수 발생

- **문제**: single line input을 token화 시킬 때 메모리 leak
- **해결**: 명령어를 파싱할 때 각 token을 연결리스트에 담고, 수행 종료 후 순차적으로 `free()`하는 미니 가비지 컬렉터 구현

### 🔸 시그널 중첩 처리 문제

- **문제**: 미니쉘 안에서 또 다른 미니쉘을 실행할 경우 시그널 중복 발생
- **해결**: 최상위 프로세스 여부를 판단하는 플래그(`is_root_shell`)를 도입하여 자식 프로세스는 시그널 무시하도록 처리

---

## 📁 디렉토리 구조

```
Jetty_minishell/
├── include/
├── exec/
│   ├── builtin/
│   ├── clean/
│   ├── run/
│   ├── signal/
│   └── main.c
├── parse/
│   ├── lexer/
│   ├── parser/
│   └── tokenizer/
├── libft/
├── Makefile
└── README.md
```

---

## 🙌 기여

> 본 프로젝트는 42서울 10기 Sewopark과 Erho가 함께 진행한 프로젝트입니다.  
> Sewopark는 프로세스 제어 및 시그널 처리, Erho는 파싱기 구현을 담당했습니다.

---

## 📜 라이선스

MIT License

---
