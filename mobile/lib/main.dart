import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'services/connectivity_service.dart';

import 'package:locky/enums/connectivity_status.dart';
import 'package:locky/screens/main_screen.dart';
import 'package:locky/services/controller.dart';
import 'package:locky/services/storage.dart';


void main() => runApp(MyApp());


class MyApp extends StatelessWidget {

  @override
  Widget build(BuildContext context) {
    PreferenceUtils.init();

    ESPController esp = ESPController(PreferenceUtils.getString("defaultEspAddress"));

    return StreamProvider<ConnectivityStatus>(
      create: (_) => ConnectivityService().connectionStatusController.stream,
      child: MaterialApp(
        title: 'Locky',
        debugShowCheckedModeBanner: false,
        home: MainScreen(),
      ),
    );

  }

}