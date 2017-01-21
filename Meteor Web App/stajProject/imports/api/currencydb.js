import { Meteor } from 'meteor/meteor';
import { Mongo } from 'meteor/mongo';
import { check } from 'meteor/check';

export const CurrencyDB = new Mongo.Collection('currencydb');

if(Meteor.isServer){
  Meteor.publish('currencydb', function currencydbPublication(){
    return CurrencyDB.find({
      owner: this.userId
    });
  });
}

Meteor.methods({
  'currencydb.insert'(getFrom, getTo, getPrice, getAmount, getRate){
    check(getFrom, String);
    check(getTo, String);
    check(getPrice, String);
    check(getAmount, String);
    check(getRate, String);

    if(!this.userId){
      throw new Meteor.Error('not-authorized');
    }

    if(getFrom === getTo){
      throw new Meteor.Error('same-currencies');
    }

    if(CurrencyDB.find({from: getFrom, to: getTo}).count() === 0){
      CurrencyDB.insert({
        from: getFrom,
        to: getTo,
        price: getPrice,
        amount: getAmount,
        rate: getRate,
        owner: this.userId,
        username: Meteor.users.findOne(this.userId).username,
      });
    }else{
      throw new Meteor.Error('already-added');
    }
  },

  'currencydb.updateprice'(taskId, getPrice){
    check(getPrice, String);

    CurrencyDB.update(taskId, {
      $set: {
        price: getPrice,
      },
    });
  },

  'currencydb.updateamount'(taskId, getAmount){
    check(getAmount, String);

    CurrencyDB.update(taskId, {
      $set: {
        amount: getAmount,
      },
    });
  },

  'currencydb.updaterate'(taskId, getRate){
    check(getRate, String);

    CurrencyDB.update(taskId, {
      $set: {
        rate: getRate,
      },
    });
  },
})
