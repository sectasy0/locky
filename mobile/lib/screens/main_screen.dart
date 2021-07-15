import 'dart:async';
import 'dart:io';

import 'package:connectivity_plus/connectivity_plus.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'package:provider/provider.dart';

import 'package:locky/globals.dart' as globals;
import 'package:locky/enums/connectivity_status.dart';
import 'package:locky/services/controller.dart';

import 'package:network_info_plus/network_info_plus.dart';


class MainScreen extends StatefulWidget {
  @override
  _MainScreenState createState() => _MainScreenState();
}

class _MainScreenState extends State<MainScreen> {
  String _url = "http://192.168.4.1";
  String _masterPassword = "\$2y\$12\$mS7a20hkrrdqV1xUwNTqdOLxHJLvRYpX/gN8brhbfSuTzCo/0dvPS"; // password hash for security

  ESPController esp = ESPController();

  Widget _buildOpenBtn() {
    return Container(
      padding: EdgeInsets.symmetric(vertical: 25.0),
      width: 350.0,
      height: 220,
      child: RaisedButton.icon(
        elevation: 5.0,
        onPressed: () async {
          try {
            await http.get(Uri.parse(_url + "/update?pass=" + _masterPassword + "&state=1"))
                  .timeout(Duration(seconds: 2));
          } on SocketException catch(e) {
            print('Faile to connect with the device');
          } on TimeoutException catch(e) {
            print('Time out');
          }
        },
        padding: EdgeInsets.all(15.0),
        icon: Icon(
            Icons.lock_open,
            color: globals.iconsColor),
        label: Text(
          'OPEN',
          style: TextStyle(
            color: Colors.black,
            letterSpacing: 2.5,
            fontSize: 18.0,
          ),
        ),
      ),
    );
  }

  Widget _buildCloseBtn() {
    return Container(
      padding: EdgeInsets.symmetric(vertical: 25.0),
      width: 350.0,
      height: 220,
      child: RaisedButton.icon(
        elevation: 5.0,
        onPressed: () async {
          print(1);
          try {
            http.get(Uri.parse(_url + "/update?pass=" + _masterPassword + "&state=1"));
          } on SocketException catch (e) {
            print('Failed to connect with the device');
          }
        },
        padding: EdgeInsets.all(15.0),
        icon: Icon(
            Icons.lock_outline,
            color: globals.iconsColor),
        label: Text(
          'CLOSE',
          style: TextStyle(
            color: Colors.black,
            letterSpacing: 2.5,
            fontSize: 18.0,
          ),
        ),
      ),
    );
  }

  Widget _buildConnectionStatus2() {
    var connectionStatus = Provider.of<ConnectivityStatus>(context);

    Widget _statusIcon(Color color) {
      return Container(
        padding: EdgeInsets.fromLTRB(20, 20, 20, 20),
        child: Icon(
          Icons.network_wifi,
          color: color,
        ),
      );
    }

    return Expanded(
      child: Align(
        alignment: Alignment.bottomLeft,
        child: FutureBuilder(
          future: (NetworkInfo().getWifiName()),
          builder: (BuildContext context, AsyncSnapshot<String> snapshot) {
            if(connectionStatus == ConnectivityStatus.WiFi){
              return _statusIcon(Colors.green);
            }
            return _statusIcon(Colors.redAccent);
          },
        ),
      ),
    );
  }

  void showAlertDialog(BuildContext context) {

    AlertDialog alert = AlertDialog(
      title: Text('Information'),
      content: Text('This feature will be available in newer version.'),
      actions: [
          TextButton(
            child: Text('OK'),
            onPressed: () {Navigator.pop(context);}
        ),
      ],
    );

    showDialog(
      context: context,
      builder: (BuildContext context) {
        return alert;
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: new AppBar(
        title: Text('Locky'),
        backgroundColor: globals.appTheme,
      ),
      body: Container(
          height: double.infinity,
          width: double.infinity,
          child: Column(
            children: <Widget>[
              SizedBox(
                height: 60,
              ),
              _buildOpenBtn(),
              _buildCloseBtn(),
              _buildConnectionStatus2(),
            ],
          )
      ),
      drawer: Drawer(
        child: ListView(
          padding: EdgeInsets.zero,
          children: <Widget>[
            DrawerHeader(
              child: new Text('Menu', style: TextStyle(color: Color.fromARGB(255, 255, 255, 255))),
              decoration: BoxDecoration(
                color: globals.appTheme,
              ),
            ),
            ListTile(
              leading: Icon(Icons.app_settings_alt_rounded),
              title: new Text('App settings'),
              onTap: () => {
                showAlertDialog(context)
              },
            ),
            ListTile(
              leading: Icon(Icons.devices_other),
              title: new Text('Device settings'),
              onTap: () => {
                showAlertDialog(context)
              },
            ),
            ListTile(
              leading: Icon(Icons.info_outline),
              title: new Text('About Locky'),
              onTap: () => {
                showAboutDialog(
                  context: context,
                  applicationVersion: '2.0.1',
                  children: <Widget>[
                    new Text('Universal car central locking remote control\n'),
                  ]
                )
              },
            ),
          ],
        ),
      ),
    );
  }

}