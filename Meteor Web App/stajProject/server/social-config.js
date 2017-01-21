import { ServiceConfiguration } from 'meteor/service-configuration';

ServiceConfiguration.configurations.remove({
  service: 'facebook'
});

ServiceConfiguration.configurations.insert({
  service: 'facebook',
  appId: '524282674435462',
  secret: '5b11f0aeebb3472707b86f228adf4d71',
});
