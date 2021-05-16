#pragma once

class UScriptStruct;

class FDataTableExFactoryUI : public TSharedFromThis<FDataTableExFactoryUI>
{
public:
	// 생성시 호출됩니다.
	FReply OnCreate();

	// 취소시 호출됩니다.
	FReply OnCancel();

	// 구초체 선택여부를 반환합니다.
	bool IsStructSelected() const;

	// 구조체 선택을 처리합니다.
	void OnPickedStruct(const UScriptStruct* chosenStruct);

	// 콤보 택스트 값을 얻는 것을 처리합니다.
	FText OnGetComboTextValue() const;

	// 구조체 선택기를 생성합니다.
	TSharedRef<SWidget> GenerateStructPicker();

	// 구조체 선택기를 엽니다.
	const UScriptStruct* OpenStructSelector();

private:
	// 선택 윈도우
	TSharedPtr<SWindow> m_pickerWindow;

	// 구조체 선택 앵커
	TSharedPtr<SComboButton> m_structPickerAnchor;

	// 결과 구조체
	const UScriptStruct* m_resultStruct = nullptr;
};
