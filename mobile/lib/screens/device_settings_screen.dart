import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

import 'package:locky/globals.dart' as globals;

class DeviceSettingsScreen extends StatefulWidget {
  @override
  _DeviceSettingsScreenState createState() => _DeviceSettingsScreenState();
}

class _DeviceSettingsScreenState extends State<DeviceSettingsScreen> {

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: new Text('Locky'),
        backgroundColor: globals.appTheme,
        leading: new IconButton(
            onPressed: () => {Navigator.pop(context)},
            icon: new Icon(Icons.arrow_back)),
      ),
    );
  }

}