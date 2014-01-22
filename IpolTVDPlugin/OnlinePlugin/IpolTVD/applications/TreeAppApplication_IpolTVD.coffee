class TreeAppApplication_IpolTVD extends TreeAppApplication
    constructor: ->
        super()
        
        @name = 'Total Variation Deconvolution'
        @powered_with = 'Ipol'
        @publication_link = 'http://www.ipol.im/pub/art/2012/g-tvdc/'
        @tutorial_link = 'http://youtu.be/TZTwBjEpfcY'

        _ina = ( app ) =>
            app.data.focus.get() != app.selected_canvas_inst()?[ 0 ]?.cm.view_id
            
        @actions.push
            ico: "img/IpolTVD_bouton.png"
            siz: 1
            txt: "Ipol Total Variation Deconvolution"
            ina: _ina
            fun: ( evt, app ) =>
                app.undo_manager.snapshot()
                ipolTVD = @add_item_depending_selected_tree app.data, IpolTVDItem

