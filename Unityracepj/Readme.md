# 최종 완성 시연영상

https://www.youtube.com/watch?v=7QGieJDK1SI

![image](https://github.com/user-attachments/assets/2b6eaa64-a5d3-486e-8b64-8a7aadd80351)

ASSETSTORE 에셋을 활용하여 직접 제작


### 제작에 사용한 에셋
https://assetstore.unity.com/packages/tools/physics/prometeo-car-controller-209444
https://assetstore.unity.com/packages/3d/environments/roadways/cartoon-race-track-oval-175061
### 초기에 사용하고 최종 버전에는 사용하지 않은 에셋
https://assetstore.unity.com/packages/3d/vehicles/land/arcade-free-racing-car-161085

### 총 제작기능 11개

트랙,자동차,카메라,자동차타이어음,자동차엔진음,체크포인트및출발선, 체크포인트시스템,속도계,현재LAP,랩타임,LAP기록

## 체크포인트 chatgpt 프롬프트

내가 유니티 3D 프로젝트로 레이싱 게임을 만드려고 해 
근데 Lap시스템을 만들면서 c#코딩을 하는데 도움이 필요해

시작점 하나랑 체크포인트 3개를 만드려고 해

시작점을 자동차가 지나가면 Lap이 1만큼 오르고 출발선이 꺼지고 다음 체크포인트1이 들어오고 
체크포인트 1을 지나가면 체크포인트 1이 꺼지고 체크포인트 2가 켜지고
체크포인트 2를 지나가면 체크포인트 2가 꺼지고 체크포인트 3이 켜지고  
체크포인트 3을 지나가면 다시 시작점이 활성화되게 하려고 해 어떻게 코딩하면 될까

(원하는 형태, 오류없는 형태의 코드가 나올때까지 새 채팅에서 사용)

## Trigger Collider Chatgpt 프롬프트
*이전 코드* 

스크립트를 외부의 Gamesystem에 올렸을땐 작동이 안되다가 Startingpoint에 올리니 딱 Startingpoint만 작동하더라 이거 원래 모든 블럭에 스크립트를 올려야하는거니?

## 타이머 기능 추가 Chatgpt 프롬프트
*이전 코드*

여기다가 실시간으로 TMP UI로 보여주는 레이싱 게임용 타이머를 추가하려고 해 시간은
분:초:마이크로초 이렇게 표시하고 싶어

맨처음 Startingpoint를 밟기 전까지는 시간이 0:00:000으로 안 흘렀으면 좋겠어
그리고 한 바퀴를 돌때마다 기록을 저장하고 싶어



## 그 외 오류 수정에 쓴 Chatgpt 프롬프트
Assets\GameSystem.cs(62,56): error CS0246: The type or namespace name 'Checkpoint' could not be found (are you missing a using directive or an assembly reference?)
Checkpoint 각각에 올려야할 스크립트는 뭐야



차의 Rigidbody에 Collision Detection이 Discrete인데 바꿔야할까

자꾸 Collider가 작동하지는 않고 통과만 되더라

시작점이랑 체크포인트 모두 설정했는데 처음에 시작점만 켜지는것 말고는 작동을 안하네 

Lines 밑에 startingline,checkpoint1,2,3들을 두긴했는데 그것때문인가/

GameObject.Find는 안써도 되는거야?

근데 왜 Textmeshpro는 안골라지고 Legacy 텍스트 UI는 골라서 올릴수 있는거야? (레거시 텍스트에서 TMP 사용가능하게 변경)

## 실패한 Chatgpt 프롬프트
Lap system 스크립트에 Text UI로 현재 Lap을 보여주고 또다른 UI는 한바퀴를 돌았을 떄 시간기록을 잴수 있게 UI를 만들어보려고 하는데 어떻게 하면 될까?
예를 들어
처음 Startingpoint를 지나가면 Lap 1의 타이머가 시작되고 다음 바퀴에서는 Lap 1의 기록이 저장되고 Lap 2의 타이머가 시작되는식
그리고 Lap3까지 돌면 여태까진 1,2,3의 Lap 시간기록과 총 걸린 시간을 보여주고 게임을 종료하게끔 하고싶어

# finalcodes
최종 완성에 사용한 코드들

### LapSystem.cs
문제점을 개선해서 완성한 최종 코드

### TriggerForwarder.cs 
트리거를 체크포인트에서 받아오기 위해 사용한 코드

### CameraFollow2.cs
카메라가 차량뒤를 원활하게 따라가게 완성한 코드,
Stackoverrflow에서 가져옴

https://stackoverflow.com/questions/65816546/unity-camera-follows-player-script

*그 외 에셋에서 가져온 코드는 미포함*


# unusedcodes
미완성 실패 코드들, 처음에 만들때 잠깐 사용했던 코드
### CameraFollow.cs
에셋을 따라가나 카메라가 부드럽게 따라가지 못하고 후면을 따라가지 않아서 실패

### GameSystem.cs
처음 프롬프트를 넣었을때 나와서 체크포인트 시스템 제작에 사용했던 코드
개선이 어려워 버리고 처음부터 다시 만듬

### LapSystem2.cs

Lap 시스템을 개선해서 기능추가에 실패한 코드
LapSystem을 개선해서 다시 만듬

