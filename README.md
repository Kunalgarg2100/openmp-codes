#Open MP codes

Usage :- ./a.out [Num of threads]

To set schedule for program, set 

| Strategy | How to set                                |
| -------- | ----------------------------------------- |
| Static   | export OMP_SCHEDULE="static, chuck-size"  |
| Dynamic  | export OMP_SCHEDULE="dynamic, chunk-size" |
| Guided   | export OMP_SCHEDULE="guided, chuck-size"  |
| Auto     | export OMP_SCHEDULE="auto"                |

https://docs.google.com/spreadsheets/d/12bM3aBkCE1B6ZJCXrr6DzSgiIoBY3BufZvZflts30zA/edit#gid=0
