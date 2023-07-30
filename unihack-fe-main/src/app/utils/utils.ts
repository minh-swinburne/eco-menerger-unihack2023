export const generateSuggestion = (history: {value: string, dateTime: string}[]) => {
    const group = 6
    let sumMaster = Array(history.length);
    let indexMaxTime = 0;
    let maxTime = -1;
    history.map((value, index) => {
        sumMaster[index] = Number(value.value) + (index == 0 ? 0 : sumMaster[index - 1])
    });

    for (let i = group - 1; i < sumMaster.length - 1; i++) {
        if ((sumMaster[i] - sumMaster[i - group - 1]) > maxTime) {
          indexMaxTime = i;
          maxTime = sumMaster[i] - sumMaster[i - group - 1]
        }
    }

    return {
        startAt: history[indexMaxTime - group - 1].dateTime.substring(10, 16),
        endAt: history[indexMaxTime].dateTime.substring(10, 16)
    }
}
