using UnityEngine;
using UnityEngine.SceneManagement;

public class GameIntro : MonoBehaviour
{
  
    // 게임 시작 버튼을 눌렀을 때 호출될 함수
    public void StartGame()
    {
        // 현재 게임 씬으로 이동 (예: "GameScene")
        SceneManager.LoadScene("GameScene");
    }
}
