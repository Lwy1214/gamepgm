using UnityEngine;
//처음 체크포인트를 제작할떄 사용한 코드, 미완성
public class GameSystem : MonoBehaviour
{
    public GameObject startingline;
    public GameObject checkpoint1;
    public GameObject checkpoint2;
    public GameObject checkpoint3;

    private int lapCount = 0; // Lap을 세는 변수
    private int currentCheckpoint = 0; // 현재 체크포인트를 추적

    void Start()
    {
        // 초기화: 시작점만 활성화
        startingline.SetActive(true);
        checkpoint1.SetActive(false);
        checkpoint2.SetActive(false);
        checkpoint3.SetActive(false);
    }

    public void ActivateCheckpoint(int checkpointID)
    {
        switch (checkpointID)
        {
            case 0: // 출발선
                lapCount++;
                Debug.Log("Lap: " + lapCount);
                startingline.SetActive(false);
                checkpoint1.SetActive(true);
                currentCheckpoint = 1;
                break;

            case 1: // 체크포인트 1
                checkpoint1.SetActive(false);
                checkpoint2.SetActive(true);
                currentCheckpoint = 2;
                break;

            case 2: // 체크포인트 2
                checkpoint2.SetActive(false);
                checkpoint3.SetActive(true);
                currentCheckpoint = 3;
                break;

            case 3: // 체크포인트 3
                checkpoint3.SetActive(false);
                startingline.SetActive(true);
                currentCheckpoint = 0;
                break;

            default:
                Debug.LogError("Invalid checkpoint ID: " + checkpointID);
                break;
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            Checkpoint checkpoint = other.GetComponent<Checkpoint>();
            if (checkpoint != null && checkpoint.checkpointID == currentCheckpoint)
            {
                Debug.Log("Player reached checkpoint: " + currentCheckpoint);
                ActivateCheckpoint(checkpoint.checkpointID);
            }
        }
    }
}
