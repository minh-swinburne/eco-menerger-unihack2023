import { Component } from '@angular/core';
import * as mock from '../mock/tenDayRecorded';
import { AngularFireDatabase, AngularFireList } from '@angular/fire/compat/database';
import { Observable, Subject, takeUntil } from 'rxjs';
import { generateSuggestion } from '../utils/utils';

@Component({
  selector: 'app-plans',
  templateUrl: './plans.component.html',
  styleUrls: ['./plans.component.scss'],
})
export class PlansComponent {
  dataListFetch;
  result: any[] = [];
  isFetch: boolean = true;

  status;
  constructor(private db: AngularFireDatabase) {
    this.dataListFetch = mock.oneDayRecordedMock;
    this.status = db.object('Device1');

    const maxW = 2000;

    let result: any[] = [];

    this.dataListFetch.map((value, index) => {

      let result1 = value.history.reduce(
        (partialSum, a) => partialSum + (Number(a.value) ?? 0),
        0
      ) / 2;

      let temp = {
        name: value.nameDevice,
        id: value.id,
        result: result1,
        message: result1 > (maxW - 100) ? 'The electricity you are consuming can be large, do you want to be optimal?' : 'Everything is OK!',
        duration: generateSuggestion(value.history)
      }

      result.push(temp)
    });

    this.result = result
  }
  observable$!: Observable<any>;
  unsubscribe$: Subject<void> = new Subject<void>();

  status1: string = "Accept optimization";
  status2: string = "Accept optimization";
  ngOnInit() {
    this.observable$ = this.db.list('DeviceList').valueChanges()
    this.observable$
      .pipe(takeUntil(this.unsubscribe$))
      .subscribe(value => {
        this.dataListFetch = value
        console.log(this.dataListFetch)
      });

    this.observable$ = this.db.list('Device1').valueChanges()
    this.observable$
      .pipe(takeUntil(this.unsubscribe$))
      .subscribe(value => {
        this.status1 = value[4]
      });

    this.observable$ = this.db.list('Device2').valueChanges()
    this.observable$
      .pipe(takeUntil(this.unsubscribe$))
      .subscribe(value => {
        this.status2 = value[4]
      });
  }
  ngOnDestroy() {
    this.unsubscribe$.next();
    this.unsubscribe$.complete();
  }

  toastTrigger: boolean = false;
  handleSetTime() {

    this.toastTrigger = true;
    this.status.update({ status: 'Pending' })
      .then(() => {
        console.log("Accept successfully")
      });

    setTimeout(() => {
      this.toastTrigger = false;
    }, 3000)
  }
  closeToast() {
    this.toastTrigger = false;
  }
}
