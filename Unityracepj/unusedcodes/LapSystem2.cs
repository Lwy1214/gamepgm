using UnityEngine;
using TMPro; // TextMeshPro 네임스페이스 추가
using UnityEngine.UI; // 버튼 관련 네임스페이스 추가
// 체크포인트에 타이머 시스템을 추가하다가 아닌것같아서 그냥 처음부터 만들기 위해 버린 코드


public class LapSystem2 : MonoBehaviour
{
    public GameObject startPoint;
    public GameObject[] checkpoints;
    public TMP_Text lapText; // TextMeshPro UI
    public TMP_Text lapTimesText; // TextMeshPro UI
    public TMP_Text totalTimeText; // TextMeshPro UI
    public Button finishButton; // 종료 버튼

    private int currentLap = 0;
    private int currentCheckpointIndex = -1;
    private float lapStartTime;
    private float totalStartTime;
    private System.Collections.Generic.List<float> lapTimes = new System.Collections.Generic.List<float>();

    void Start()
    {
        totalStartTime = Time.time;
        lapStartTime = Time.time;

        ActivatePoint(startPoint);
        foreach (var checkpoint in checkpoints)
        {
            checkpoint.SetActive(false);
        }

        finishButton.gameObject.SetActive(false); // 종료 버튼 비활성화
        UpdateLapUI();
    }

    public void OnCheckpointTriggered(GameObject checkpoint, Collider other)
    {
        if (!other.CompareTag("Player")) return;

        if (checkpoint == startPoint)
        {
            if (currentCheckpointIndex == checkpoints.Length - 1 || currentCheckpointIndex == -1)
            {
                currentLap++;
                SaveLapTime();

                if (currentLap > 3) // 마지막 Lap 완료 시
                {
                    FinishRace();
                    return;
                }

                lapStartTime = Time.time; // 다음 Lap 시작
                currentCheckpointIndex = 0;
                ActivatePoint(checkpoints[currentCheckpointIndex]);
            }
        }
        else if (currentCheckpointIndex >= 0 && checkpoint == checkpoints[currentCheckpointIndex])
        {
            checkpoints[currentCheckpointIndex].SetActive(false);
            currentCheckpointIndex++;

            if (currentCheckpointIndex >= checkpoints.Length)
            {
                ActivatePoint(startPoint);
            }
            else
            {
                ActivatePoint(checkpoints[currentCheckpointIndex]);
            }
        }

        UpdateLapUI();
    }

    private void SaveLapTime()
    {
        float lapTime = Time.time - lapStartTime; // 현재 Lap 시간 계산
        lapTimes.Add(lapTime);

        lapTimesText.text += $"Lap {currentLap}: {lapTime:F2} sec\n"; // Lap 시간 기록 추가
    }

    private void UpdateLapUI()
    {
        lapText.text = $"Lap: {currentLap + 1}";
        totalTimeText.text = $"Total Time: {Time.time - totalStartTime:F2} sec";
    }

    private void FinishRace()
    {
        float totalTime = Time.time - totalStartTime;

        // 최종 결과 표시
        lapTimesText.text += "\n--- Final Results ---\n";
        for (int i = 0; i < lapTimes.Count; i++)
        {
            lapTimesText.text += $"Lap {i + 1}: {lapTimes[i]:F2} sec\n";
        }
        lapTimesText.text += $"Total Time: {totalTime:F2} sec";

        // 종료 버튼 활성화
        finishButton.gameObject.SetActive(true);
        finishButton.onClick.RemoveAllListeners(); // 기존 리스너 제거
        finishButton.onClick.AddListener(() => Application.Quit()); // 버튼 클릭 시 게임 종료
    }

    private void ActivatePoint(GameObject point)
    {
        if (point != null)
            point.SetActive(true);
    }
}
