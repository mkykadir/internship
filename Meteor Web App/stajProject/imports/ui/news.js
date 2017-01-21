import { Template } from 'meteor/templating';
import { Mongo } from 'meteor/mongo';
import { NewsDB } from '../api/newsdb.js';
import './news.html';

Template.news.helpers({
  newsdb(){
    return NewsDB.find({}, { sort: { createdAt: -1 } });
  },

  hideul(){
    if(NewsDB.find({}).count() === 0){
      return true;
    }else{
      return false;
    }
  },
});

Template.news.events({
  'click #refresh-menu'(event){
    event.preventDefault();

    Meteor.call('newsdb.insert', "/img/news-deneme.png", "", "", "", function(error){
      if(error){
        switch (error.error) {
          case "not-authorized":
            alert("Bu veriye erişebilmek için giriş yapmanız gerekmektedir.");
            break;
          default:
            alert("Bilinmeyen hata!");
            break;
        }
      }
    });
  },

  'click .clickable'(event){
    event.preventDefault();
    var curId = this._id;
    Meteor.call('getNewsImage', function(error, response){
      if(error){
        console.log(error, error);
      }else{
        Meteor.call('newsdb.updateimg', curId, response);
      }
    });

    Meteor.call('getNewsTitle', function(error, response){
      if(error){
        console.log(error, error);
      }else{
        Meteor.call('newsdb.updatetitle', curId, response);
      }
    });

    Meteor.call('getNewsContent', function(error, response){
      if(error){
        console.log(error, error);
      }else{
        Meteor.call('newsdb.updatecontent', curId, response);
      }
    });

    Meteor.call('getNewsLink', function(error, response){
      if(error){
        console.log(error, error);
      }else{
        Meteor.call('newsdb.updatelink', curId, response);
      }
    });
  }
});
