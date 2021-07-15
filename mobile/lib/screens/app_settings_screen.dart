import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

import 'package:locky/globals.dart' as globals;

class AppSettingsScreen extends StatefulWidget {
  @override
  _AppSettingsScreenState createState() => _AppSettingsScreenState();
}

class _AppSettingsScreenState extends State<AppSettingsScreen> {

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