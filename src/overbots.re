[%bs.raw {|require('./overbots.scss')|}];

open Tea;

open Overbots_types;

let init () => {
  let model = {
    msg: [],
    resource_values = Overbots_resources.init_resources_values (),
    bool_flags: init_bool_flags (),
    int_flag: init_int_flags (),
  };
  (model, Cmd.none)
};

let update model msg =>
  switch msg {
  | NothingYet => (model, Cmd.none)
  };

let subscriptions _model => Sub.none;

let main = App.standardProgram {init, update, view: Overbots_view.view, subscriptions};

let overbotsRoot = [%bs.raw {|document.getElementById('overbots')|}];

/* Web.Document.getElementById "overbots" */
main overbotsRoot ();
