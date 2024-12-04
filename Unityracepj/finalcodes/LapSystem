using UnityEngine;
using TMPro;
using System.Diagnostics; // Stopwatch 사용
using System.Collections.Generic; // 리스트 사용

public class LapSystem : MonoBehaviour
{
    public GameObject startPoint;
    public GameObject[] checkpoints;
    public TMP_Text CurrentLap;
    public TMP_Text TimerText; // 타이머 UI 텍스트
    public TMP_Text LapTimesText; // 랩 타임 기록 UI 텍스트

    private int currentCheckpointIndex = -1;
    private int lapCount = 0;

    private Stopwatch stopwatch;
    private List<string> lapRecords; // 랩 기록 저장 리스트

    void Start()
    {
        // 초기화
        ActivatePoint(startPoint);
        foreach (var checkpoint in checkpoints)
        {
            checkpoint.SetActive(false);
        }

        stopwatch = new Stopwatch();
        lapRecords = new List<string>();
        TimerText.text = "Time: 0:00:000";
    }

    void Update()
    {
        // 타이머 업데이트
        if (stopwatch.IsRunning)
        {
            UpdateTimerUI();
        }
    }

    public void OnCheckpointTriggered(GameObject checkpoint, Collider other)
    {
        if (!other.CompareTag("Player")) return;

        if (checkpoint == startPoint) // 시작점
        {
            if (lapCount > 0)
            {
                // 이전 랩 기록 저장
                string lapTime = FormatTime(stopwatch.Elapsed);
                lapRecords.Add("Lap " + lapCount + ": " + lapTime);
                UpdateLapRecordsUI();
            }

            lapCount++;
            UnityEngine.Debug.Log("Lap: " + lapCount);
            CurrentLap.text = "Lap: " + lapCount;

            // 새 랩 시작 시 타이머 리셋
            stopwatch.Restart();

            startPoint.SetActive(false);
            currentCheckpointIndex = 0;
            ActivatePoint(checkpoints[currentCheckpointIndex]);
        }
        else if (currentCheckpointIndex >= 0 && checkpoint == checkpoints[currentCheckpointIndex]) // 체크포인트
        {
            checkpoints[currentCheckpointIndex].SetActive(false);
            currentCheckpointIndex++;
            UnityEngine.Debug.Log("Checkpoint: " + currentCheckpointIndex);

            if (currentCheckpointIndex >= checkpoints.Length) // 마지막 체크포인트
            {
                currentCheckpointIndex = -1;
                ActivatePoint(startPoint);
            }
            else
            {
                ActivatePoint(checkpoints[currentCheckpointIndex]);
            }
        }
        else if (lapCount == 0 && checkpoint == startPoint) // 처음 시작점
        {
            // 타이머 시작
            stopwatch.Start();
        }
    }

    private void ActivatePoint(GameObject point)
    {
        if (point != null)
            point.SetActive(true);
    }

    private void UpdateTimerUI()
    {
        var timeSpan = stopwatch.Elapsed;

        // 시간 형식: 분:초:밀리초
        TimerText.text = "Time: " + FormatTime(timeSpan);
    }

    private string FormatTime(System.TimeSpan timeSpan)
    {
        return string.Format("{0:0}:{1:00}:{2:000}",
            timeSpan.Minutes,
            timeSpan.Seconds,
            timeSpan.Milliseconds);
    }

    private void UpdateLapRecordsUI()
    {
        LapTimesText.text = string.Join("\n", lapRecords);
    }
}
