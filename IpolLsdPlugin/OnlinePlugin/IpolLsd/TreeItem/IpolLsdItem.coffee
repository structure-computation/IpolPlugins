#
class IpolLsdItem extends TreeItem_Computable
    constructor: ( name = "IpolLsd" ) ->
        super()

        @add_attr
            scale      : new ConstrainedVal( 1.0, { min: 0.0 } )
            sigma_coef : new ConstrainedVal( 0.6, { min: 0.0 } )
            quant      : new ConstrainedVal( 2.0, { min: 0.0 } )
            ang_th     : new ConstrainedVal(22.5, { min: 0.0, max: 180.0 } )
            log_eps    : 0.0
            density_th : new ConstrainedVal( 0.7, { min: 0.0, max: 1.0  } )
            n_bins     : new ConstrainedVal( 1  , { min:   1, max: 1024, div: 1024 } )
            #reg        : ""
            #epsfile    : ""
            #svgfile    : ""
            width      : 1.5
        
        @_name.set name
        #@_ico.set "img/scilab.png"
        @_viewable.set false
        @_computation_mode.set false
        
        #@add_child new ImgSetItem
        @add_output new ImgItem
    
    
    accept_child: ( ch ) ->
        ch instanceof ImgItem or
        ch instanceof FileItem
    
    
    z_index: ->
        #@_mesh.z_index()

