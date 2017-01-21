import { Meteor } from 'meteor/meteor';
import { Mongo } from 'meteor/mongo';
import { check } from 'meteor/check';

export const NewsDB = new Mongo.Collection('newsdb');


if(Meteor.isServer){
  Meteor.publish('newsdb', function newsdbPublication(){
    return NewsDB.find({
      owner: this.userId
    }, { sort: { createdAt: -1 } });
  });
}

Meteor.methods({
  'newsdb.insert'(getImg, getTitle, getContent, getLink){
      check(getImg, String);
      check(getTitle, String);
      check(getContent, String);
      check(getLink, String);


      if(!this.userId){
        throw new Meteor.Error('not-authorized');
      }

      NewsDB.insert({
        img: getImg,
        title: getTitle,
        content: getContent,
        link: "http://www.ensonhaber.com/" + getLink,
        createdAt: new Date(),
        owner: this.userId,
        username: Meteor.users.findOne(this.userId).username,
      });

  },

  'newsdb.updateimg'(getId, getImg){
    check(getImg, String);

    NewsDB.update(getId, {
      $set: { img: getImg },
    });
  },

  'newsdb.updatetitle'(getId, getTitle){
    check(getTitle, String);

    if(NewsDB.find({ title: getTitle }).count() === 0){
      NewsDB.update(getId, {
        $set: { title: getTitle },
      });
    }else{
      //if(NewsDB.find({title: getTitle}).count() !== 1){
        NewsDB.remove(getId);
      //}
    }
  },

  'newsdb.updatecontent'(getId, getContent){
    check(getContent, String);

    NewsDB.update(getId, {
      $set: { content: getContent},
    });
  },

  'newsdb.updatelink'(getId, getLink){
    check(getLink, String);

    NewsDB.update(getId,{
      $set: { link: "http://www.ensonhaber.com" + getLink },
    });
  },
});
