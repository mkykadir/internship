import { Meteor } from 'meteor/meteor';
import { Template } from 'meteor/templating';

Template.login.events({
  'click #facebook-login'(event){
    event.preventDefault();
    Meteor.loginWithFacebook({}, function(err){
      if(err){
        throw new Meteor.error("facebook login failed");
      }
    });
  },

  'click #logout'(event){
    Meteor.logout(function(err){
      if(err){
        throw new Meteor.error("Logout failed");
      }
    });
  }
});
