import { Meteor } from 'meteor/meteor';
import { Mongo } from 'meteor/mongo';
import { check } from 'meteor/check';

export const MainGrid = new Mongo.Collection('maingriddb');


if(Meteor.isServer){
  Meteor.publish('maingriddb', function maingriddbPublication(){
    return MainGrid.find({
      owner: this.userId
    });
  });
}

Meteor.methods({
  'maingriddb.insert'(type, data){
    check(type, String);
    check(data, String);
    //check(text, String);

    if(!this.userId){
      throw new Meteor.Error('not-authorized');
    }

    MainGrid.insert({
      contentType: type,
      contentData: data,
      //contentText: text,
      owner: this.userId,
      username: Meteor.users.findOne(this.userId).username,
    });
  },
});
