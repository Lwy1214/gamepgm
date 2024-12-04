using UnityEngine;
//시작점, 체크포인트에 추가한 코드
public class TriggerForwarder : MonoBehaviour
{
    public LapSystem lapSystem; // LapSystem의 참조

    private void OnTriggerEnter(Collider other)
    {
        if (lapSystem != null)
        {
            lapSystem.OnCheckpointTriggered(gameObject, other);
        }
    }
}
