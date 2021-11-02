/* Copyright 2021 CapsUnlocked
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum {
    _MEDIA = 0,
    _FUNC,
    _TEST,
    _LAST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MEDIA] = LAYOUT(
           KC_AUDIO_MUTE,
    TO(0), TO(1), TO(2),
    KC_MPRV, KC_MEDIA_PLAY_PAUSE, KC_MNXT
  ),
  [_FUNC] = LAYOUT(
        KC_AUDIO_MUTE,
    TO(0), TO(1), TO(2),
    KC_WWW_REFRESH, KC_WWW_BACK, KC_WWW_FORWARD
  ),
  [_TEST] = LAYOUT(
          KC_AUDIO_MUTE,
    TO(0), TO(1), TO(2),
    KC_CALCULATOR, KC_MY_COMPUTER, KC_C
  ),
  [_LAST] = LAYOUT(
          KC_AUDIO_MUTE,
    TO(0), TO(1), TO(2),
    KC_A, KC_B, KC_C
  ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
		switch(biton32(layer_state)){
			case _MEDIA:
				if (clockwise) {
					tap_code_delay(KC_VOLU, 10);
				}
				else {
					tap_code_delay(KC_VOLD, 10);
				}
				break;
			case _FUNC:
				if (clockwise) {
          tap_code_delay(KC_MS_WH_DOWN, 0);
				}
				else {
          tap_code_delay(KC_MS_WH_UP, 0);
				}
        break;
      case _TEST:
				if (clockwise) {
					tap_code_delay(KC_MS_WH_RIGHT, 0);
				}
				else {
					tap_code_delay(KC_MS_WH_LEFT, 0);
				}
        break;
			default: //the default layer is the same as the first layer, in this case _PSHOP
        if (clockwise) {
          tap_code_delay(KC_VOLU, 10);
        }
        else {
          tap_code_delay(KC_VOLD, 10);
        }
		}
		return true;
};

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {0,6,HSV_PURPLE}
);

const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {0,6,HSV_WHITE}
);

const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {0,6,HSV_CYAN}
);

const rgblight_segment_t PROGMEM caps_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {0,6,HSV_RED}
);


const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
  my_layer1_layer,
  my_layer2_layer,
  my_layer3_layer,
  caps_layer3_layer
);

bool led_update_user(led_t led_state) {
  rgblight_set_layer_state(3, led_state.caps_lock);
  return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(0, layer_state_cmp(state, _MEDIA));
  return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(0, layer_state_cmp(state, _MEDIA));
  rgblight_set_layer_state(1, layer_state_cmp(state, _FUNC));
  rgblight_set_layer_state(2, layer_state_cmp(state, _TEST));
  return state;
};

void keyboard_post_init_user(void) {
  rgblight_layers = my_rgb_layers;
};