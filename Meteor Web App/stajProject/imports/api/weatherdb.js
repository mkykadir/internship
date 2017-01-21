import { Meteor } from 'meteor/meteor';
import { Mongo } from 'meteor/mongo';
import { check } from 'meteor/check';

export const WeatherDB = new Mongo.Collection('weatherdb');


if(Meteor.isServer){
  Meteor.publish('weatherdb', function weatherdbPublication(){
    return WeatherDB.find({
      owner: this.userId
    });
  });
}

Meteor.methods({
  'weatherdb.insert'(getImage, getCity, getTemp, getHigh, getLow, getPressure, getHumidty, getRain){
    check(getImage, String);
    check(getCity, String);
    check(getTemp, String);
    check(getHigh, String);
    check(getLow, String);
    check(getPressure, String);
    check(getHumidty, String);
    check(getRain, String);
    //check(text, String);

    if(!this.userId){
      throw new Meteor.Error('not-authorized');
    }

    if(WeatherDB.find({ city: getCity }).count() === 0){
      WeatherDB.insert({
        image: getImage,
        city: getCity,
        temp: getTemp,
        high: getHigh,
        low: getLow,
        pressure: getPressure,
        humidty: getHumidty,
        rain: getRain,
        owner: this.userId,
        username: Meteor.users.findOne(this.userId).username,
      });
    }else{
      throw new Meteor.Error('already-added');
    }

  },

  'weatherdb.updatetemp'(taskId, getTemp){
    check(getTemp, String);
    WeatherDB.update(taskId, {
      $set: { temp: getTemp },
    });
  },

  'weatherdb.updateimage'(taskId, getImage){
    check(getImage, String);
    WeatherDB.update(taskId, {
        $set: { image: getImage },
    });
  },

  'weatherdb.updatehigh'(taskId, getHigh){
    check(getHigh, String);
    WeatherDB.update(taskId, {
      $set: { high: getHigh },
    });
  },

  'weatherdb.updatelow'(taskId, getLow){
    check(getLow, String);
    WeatherDB.update(taskId, {
      $set: { low: getLow },
    });
  },

  'weatherdb.updatepressure'(taskId, getPressure){
    check(getPressure, String);
    WeatherDB.update(taskId, {
      $set: { pressure: getPressure },
    });
  },

  'weatherdb.updatehumidty'(taskId, getHumidty){
    check(getHumidty, String);
    WeatherDB.update(taskId, {
      $set: { humidty: getHumidty },
    });
  },

  'weatherdb.updaterain'(taskId, getRain){
    check(getRain, String);
    WeatherDB.update(taskId, {
      $set: { rain: getRain },
    });
  },
});
